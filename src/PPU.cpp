#include "PPU.h"

void PPU::UpdatePPU(uint8_t TcyclesSinceLastUpdate) {
    TcyclesSinceLastScanline += TcyclesSinceLastUpdate;
    if (TcyclesSinceLastScanline > 456) {
        currentScanline++;
    }

    //if we just hit 80 t cycles and we haven't read OAM yet, now is the time to do that
    //this takes the first 10 sprites that need to be rendered and places them into the internal sprite buffer
    if (TcyclesSinceLastScanline > 80 && !modesCompleted[2]) {
        for (int i = 0; i < totalSprites; i++) {
            //times 4 since there are 4 bytes per sprite, 40 sprites total
            uint8_t curSpriteYValue = gb.read(OAMStartAddress + i*bytesPerSprite);
            if (currentScanline >= (curSpriteYValue - 16) &&
                currentScanline < (curSpriteYValue - 16 + spriteHeight())) {

                Sprite s{gb.read(OAMStartAddress + i*bytesPerSprite),
                gb.read(1 +OAMStartAddress + i*bytesPerSprite),
                gb.read(2 + OAMStartAddress + i*bytesPerSprite),
                gb.read(3 + OAMStartAddress + i*bytesPerSprite)
                };

                //increment after using
                spriteBuffer[nextEmptySlot++] = s;

                if (nextEmptySlot > sizeof(spriteBuffer) * bytesPerSprite) {
                    break;
                }

            }
        }
    }
}

void PPU::BeginNewFrame() {
    TcyclesSinceLastScanline = 0;
    currentScanline = 0;
    currentMode = 2;
    std::fill(std::begin(modesCompleted), std::end(modesCompleted), false);
}


