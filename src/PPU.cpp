#include "PPU.h"
#include "Memory.h"

#include <iostream>
#include <array>
#include <SDL2/SDL_render.h>

PPU::PPU(Memory& m) : mem(m) {
    mem.WriteScanline(currentScanline, MemoryAccessor::PPU);
    mem.setOAMDisabled(true);
}

void PPU::UpdatePPU(uint8_t TcyclesSinceLastUpdate) {
    TcyclesSinceLastScanline += TcyclesSinceLastUpdate;

    if (TcyclesSinceLastScanline >= 456 && currentMode == PPUMode::HBlank) {
        //reset to a new line, subtracting 456 also keeps overflow if it exists
        currentScanline++;
        nextEmptySlot = 0;
        mem.WriteScanline(currentScanline, MemoryAccessor::PPU);
        TcyclesSinceLastScanline -= 456;
        mem.setOAMDisabled(false);
        if (currentScanline >= 144) {
            currentMode = PPUMode::VBlank;
        } else {
            currentMode = PPUMode::OAM;
            mem.setOAMDisabled(true);
        }
    }

    //252 = 80 + 172
    else if(TcyclesSinceLastScanline >= (252) && currentMode == PPUMode::Draw) {
        uint32_t scanline[160]{};
        uint8_t bgWindowScanline[160]{};

        DrawBackground(scanline, bgWindowScanline);
        if (windowEnabled() && currentScanline >= windowStartY()) {
            DrawWindow(scanline, bgWindowScanline);
            windowLinesWritten++;
        }


        if (spritesEnabled()) {
            DrawSprites(scanline, bgWindowScanline);
        }


        //copy the current scanline into our framebuffer
        std::copy(std::begin(scanline), std::end(scanline),
            frameBuffer[currentScanline]);

        currentMode = PPUMode::HBlank;
        mem.setOAMDisabled(false);
    }

    //if we just hit 80 t cycles and we haven't read OAM yet, now is the time to do that
    //this takes the first 10 sprites that need to be rendered and places them into the internal sprite buffer
    else if (TcyclesSinceLastScanline >= 80 && currentMode == PPUMode::OAM) {
        for (uint8_t i = 0; i < totalSprites; i++) {
            //times 4 since there are 4 bytes per sprite, 40 sprites total
            uint16_t firstByte = OAMStartAddress + i*bytesPerSprite;
            uint8_t curSpriteYValue = Read(firstByte);
            if (currentScanline < (curSpriteYValue - 16) ||
                currentScanline >= (curSpriteYValue - 16 + spriteHeight())) {
                continue;
            }

            Sprite s{Read(firstByte), Read(1 + firstByte),
            Read(2 + firstByte), Read(3 + firstByte), i};

            //increment after using
            spriteBuffer[nextEmptySlot++] = s;

            if (nextEmptySlot >= 10) {
                break;
            }

        }

        //lambda function to sort the sprite buffer first by the lower x value and if these are the same,
        //the lower OAM index
        std::sort(std::begin(spriteBuffer), std::end(spriteBuffer),
            [](const Sprite &a, const Sprite &b) {
            if (a.x != b.x) { return a.x < b.x; }
                return a.OAMIndex < b.OAMIndex;
        });

        currentMode = PPUMode::Draw;
    }

    else if (TcyclesSinceLastScanline >= 456 && currentMode == PPUMode::VBlank) {
        currentScanline++;
        nextEmptySlot = 0;
        TcyclesSinceLastScanline -= 456;
        if (currentScanline >= 154) {
            currentScanline = 0;
            windowLinesWritten = 0;
            mem.WriteScanline(currentScanline, MemoryAccessor::PPU);
            currentMode = PPUMode::OAM;
            mem.setOAMDisabled(true);
        }
    }
    mem.setMode(currentMode);
}

void PPU::DrawBackground(uint32_t *scanline, uint8_t *bgWindowScanline) {
    //iterates through every pixel in scanline
    for(uint8_t pixel = 0; pixel < 160; pixel++) {
        //background pixel detection
        //scroll registers tell us how far right and how far down we have scrolled
        uint8_t xScroll = Read(0xFF43);
        uint8_t yScroll = Read(0xFF42);

        //this is the current pixel we are on in the 256x256 grid
        uint8_t xPixel = xScroll + pixel;
        uint8_t yPixel = yScroll + currentScanline;

        //current tile we are on in 32x32 tile map
        uint8_t xTile = (xPixel & 0xFF) / 8;
        uint8_t yTile = (yPixel & 0xFF) / 8;

        uint16_t tileMapStartAddress = LCDCBit3Tilemaps() ? 0x9C00 : 0x9800;

        //current tileID
        uint8_t currentTile = Read(tileMapStartAddress + (yTile * 32) + xTile);

        //loads tileData, each 2 rows of this represent the color data of one row of pixels
        std::array<uint8_t, 16> tileData = mem.ReadTile(currentTile);

        uint8_t tileColumn = 7 - (xPixel % 8);
        uint8_t tileRow = yPixel % 8;

        //extracting the color ID from the two rows representing the pixel
        uint8_t pixelColor{};
        pixelColor = (tileData[tileRow * 2] & (0x01 << tileColumn)) >> tileColumn;
        pixelColor |= ((tileData[(tileRow * 2) + 1] & (0x01 << tileColumn)) >> tileColumn) << 1u;

        //then grab the shade this colorID represents from
        uint8_t shade = (Read(0xFF47) & (0x03 << (pixelColor * 2))) >> (pixelColor * 2);
        bgWindowScanline[pixel] = shade;
        scanline[pixel] = colors[shade];
    }
}


void PPU::DrawWindow(uint32_t *scanline, uint8_t *bgWindowScanline) {
    //iterates through every pixel in scanline
    for(uint8_t pixel = 0; pixel < 160; pixel++) {
        //the current x position is offset by 7, so the window starts at 7 less than what is in the register
        //if the window start x is 7, we start drawing at (in our minds) x=0
        if (pixel < (windowStartX() - 7)) {
            continue;
        }

        //window tilemap does not utilize scroll, everything starts at top left
        //the subtraction basically "pulls" us back to the beginning of the tilemap and gets how far we are from
        //there by calculating the actual pixel value
        //this is converting from screen pixel to how many pixels we are into drawing the window
        uint8_t xPixel = pixel - (windowStartX() - 7);
        uint8_t yPixel = windowLinesWritten;


        //current tile we are on in 32x32 tile map
        //xtile calculates the pixel minus where we are supposed to start which tells you how far into the window
        //tilemap you are. if the window is meant to start on screen pixel 0, windowStartX() will be 7
        //so subtracting (start - 7) will yield how many pixels we are actually into the tilemap
        //so we will pull the correct one. if pixel is 10 in this case, we want to render the first tile
        //not the 0th one

        uint8_t xTile = (xPixel & 0xFF) / 8;
        uint8_t yTile = (yPixel & 0xFF) / 8;

        uint16_t tileMapStartAddress = LCDCBit6Tilemaps() ? 0x9C00 : 0x9800;

        //current tileID
        uint8_t currentTile = Read(tileMapStartAddress + (yTile * 32) + xTile);

        //loads tileData, each 2 rows of this represent the color data of one row of pixels
        std::array<uint8_t, 16> tileData = mem.ReadTile(currentTile);

        uint8_t tileColumn = 7 - (xPixel % 8);
        uint8_t tileRow = yPixel % 8;

        //extracting the color ID from the two rows representing the pixel
        uint8_t pixelColor{};
        pixelColor = (tileData[tileRow * 2] & (0x01 << tileColumn)) >> tileColumn;
        pixelColor |= ((tileData[(tileRow * 2) + 1] & (0x01 << tileColumn)) >> tileColumn) << 1u;

        //then grab the shade this colorID represents from
        uint8_t shade = (Read(0xFF47) & (0x03 << (pixelColor * 2))) >> (pixelColor * 2);
        bgWindowScanline[pixel] = shade;
        scanline[pixel] = colors[shade];
    }
}


void PPU::DrawSprites(uint32_t *scanline, uint8_t *bgWindowScanline) {
    //iterates through every pixel in scanline
    for(uint8_t pixel = 0; pixel < 160; pixel++) {
        for (int i = 0; i < 10; i++) {
            Sprite s = spriteBuffer[i];
            //sprite.x stores the starting x position + 8 (same as ending x position),
            //so x >= s.x-8 and x < s.x means sprite is rendered on this pixel
            if (pixel < (s.x - 8) || pixel >= s.x) {
                continue;
            }

            //say we are on pixel 5 and the sprite.x is pixel 10. then, sprite ends on pixel 10 (not inclusive), and
            //it starts on pixel 2. subtract (s.x-8) will subtract 2 and get us 3, we basically pull back the sprite
            //and pixel to see where it falls in a relative sense to the pixel width
            //y is the same but offset is 16
            uint8_t spriteX =  pixel - (s.x - 8);
            uint8_t spriteY = currentScanline - (s.y - 16);

            //flip if the flip flags are set
            if (SpriteFlagBitValue(s, 5)) { spriteX = 7 - spriteX; }
            if (SpriteFlagBitValue(s, 6)) { spriteY = (spriteHeight()-1) - spriteY; }

            std::array<uint8_t, 16> tileData;
            if (spriteHeight() == 16) {
                if (spriteY >= 8) {
                    tileData = mem.ReadTile(s.tile | 0x01);
                    spriteY -= 8;
                } else {
                    tileData = mem.ReadTile(s.tile & 0xFE);
                }
            } else {
                tileData = mem.ReadTile(s.tile);
            }

            uint8_t pixelColor{};
            pixelColor = (tileData[spriteY * 2] & (0x01 << (7-spriteX))) >> (7-spriteX);
            pixelColor |= ((tileData[(spriteY * 2) + 1] & (0x01 << (7-spriteX))) >> (7-spriteX)) << 1u;

            //if the pixelcolor is 0, its transparent so we skip it
            if (pixelColor == 0) { continue; }

            //s.flags & 0x80 is the priority bit, determines whether sprite gets priority over bg and window
            //
            if (s.flags & 0x80) {
                if (bgWindowScanline[pixel] == 0) {
                    uint16_t paletteAddress = SpriteFlagBitValue(s, 4) ? 0xFF49 : 0xFF48;
                    uint8_t shade = (Read(paletteAddress) & (0x03 << (pixelColor * 2))) >> (pixelColor * 2);
                    scanline[pixel] = colors[shade];
                    break;
                } else {
                    continue;
                }
            }
            //if bit 4 is 1, we use the palette values in FF49, otherwise FF48
            uint16_t paletteAddress = SpriteFlagBitValue(s, 4) ? 0xFF49 : 0xFF48;
            uint8_t shade = (Read(paletteAddress) & (0x03 << (pixelColor * 2))) >> (pixelColor * 2);
            scanline[pixel] = colors[shade];
            break;
        }
    }
}

