#include "PPU.h"

#include <SDL2/SDL_render.h>

PPU::PPU(Memory& m) : mem(m) {
    mem.WriteScanline(currentScanline);
    mem.setOAMDisabled(true);
}

void PPU::UpdatePPU(uint8_t TcyclesSinceLastUpdate) {
    TcyclesSinceLastScanline += TcyclesSinceLastUpdate;

    if (TcyclesSinceLastScanline >= 456 && currentMode == PPUMode::HBlank) {
        //reset to a new line, subtracting 456 also keeps overflow if it exists
        currentScanline++;
        mem.WriteScanline(currentScanline);
        TcyclesSinceLastScanline -= 456;
        mem.setOAMDisabled(false);
        if (currentScanline >= 143) {
            currentMode = PPUMode::VBlank;
        } else {
            currentMode = PPUMode::OAM;
            mem.setOAMDisabled(true);
        }
    }

    //252 = 80 + 172
    else if(TcyclesSinceLastScanline >= (252) && currentMode == PPUMode::Draw) {
        uint32_t scanline[160]{};
        //iterates through every pixel
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

            uint16_t tileMapStartAddress = currentTileMap() ? 0x9C00 : 0x9800;

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
            uint8_t shade = (Read(0xFF47) & (0x03 << (pixelColor * 2))) << (pixelColor * 2);

            scanline[pixel] = colors[shade];
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
            Read(2 + firstByte), Read(3 + firstByte)};

            //increment after using
            spriteBuffer[nextEmptySlot++] = s;

            if (nextEmptySlot > sizeof(spriteBuffer) * bytesPerSprite) {
                break;
            }

        }
        currentMode = PPUMode::Draw;
    }

    else if (TcyclesSinceLastScanline >= 456 && currentMode == PPUMode::VBlank) {
        currentScanline++;
        mem.WriteScanline(currentScanline);
        TcyclesSinceLastScanline -= 456;
        if (currentScanline >= 154) {
            currentScanline = 0;
        }
    }
}


