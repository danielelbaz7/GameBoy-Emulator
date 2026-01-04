#include "PPU.h"

void PPU::UpdatePPU(uint8_t TcyclesSinceLastUpdate) {
    TcyclesSinceLastScanline += TcyclesSinceLastUpdate;
    if (TcyclesSinceLastScanline > 456) {
        currentScanline++;
    }

    //if we just hit 80 t cycles and we haven't read OAM yet, now is the time to do that
    //this takes the first 10 sprites that need to be rendered and places them into the internal sprite buffer
    if (TcyclesSinceLastScanline > 80 && currentMode == PPUMode::OAM) {
        for (int i = 0; i < totalSprites; i++) {
            //times 4 since there are 4 bytes per sprite, 40 sprites total
            uint8_t curSpriteYValue = mem.read(OAMStartAddress + i*bytesPerSprite);
            if (currentScanline < (curSpriteYValue - 16) ||
                currentScanline >= (curSpriteYValue - 16 + spriteHeight())) {
                continue;
            }

            Sprite s{mem.read(curSpriteYValue), mem.read(1 + curSpriteYValue),
            mem.read(2 + curSpriteYValue),mem.read(3 + curSpriteYValue)};

            //increment after using
            spriteBuffer[nextEmptySlot++] = s;

            if (nextEmptySlot > sizeof(spriteBuffer) * bytesPerSprite) {
                break;
            }

        }
        currentMode = PPUMode::Draw;
    }
}

