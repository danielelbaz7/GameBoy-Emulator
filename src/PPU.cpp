#include "PPU.h"

PPU::PPU(Memory& m) : mem(m) {
    mem.WriteScanline(currentScanline);
    mem.setOAMDisabled(true);
    
}

void PPU::UpdatePPU(uint8_t TcyclesSinceLastUpdate) {
    TcyclesSinceLastScanline += TcyclesSinceLastUpdate;
    if (TcyclesSinceLastScanline > 456) {
        currentScanline++;
    }

    if(TcyclesSinceLastScanline >= (80 + 172) && currentMode == PPUMode::Draw) {
        //iterates through every pixel
        for(uint8_t pixel = 0; pixel < 160; pixel++) {
            //background pixel detection
            //scroll registers tell us how far right and how far down we have scrolled
            uint8_t xScroll = Read(0xFF43);
            uint8_t yScroll = Read(0xFF42);

            uint8_t xTile = ((xScroll + pixel) & 0xFF) / 8;
            uint8_t yTile = ((yScroll + currentScanline) & 0xFF) / 8;
            
            uint8_t currentTile = Read((yTile * 32) + xTile);

            uint8_t tileData[16] = mem.ReadTile(currentTile);

        }
    }

    //if we just hit 80 t cycles and we haven't read OAM yet, now is the time to do that
    //this takes the first 10 sprites that need to be rendered and places them into the internal sprite buffer
    if (TcyclesSinceLastScanline >= 80 && currentMode == PPUMode::OAM) {
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
}

