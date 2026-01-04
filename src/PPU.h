#ifndef GAMEBOYEMULATOR_PPU_H
#define GAMEBOYEMULATOR_PPU_H
#include "Gameboy.h"

class PPU {
public:
    explicit PPU(Gameboy& gb) : gb(gb)  {};
    void UpdatePPU(uint8_t TcyclesSinceLastUpdate);

private:
    Gameboy& gb;
    unsigned int TcyclesSinceLastScanline{};
    uint8_t currentScanline{}; //goes from 0-153, last 10 are vblank
    uint8_t currentMode{2};
    bool modesCompleted[4]{}; //mode 2 is OAM, then mode 3 is drawing pixels,
    //then mode 0 is horizontal blank, and mode 1 is vertical blank

    //lambda function that returns the current sprite height at any point
    [[nodiscard]] uint8_t spriteHeight() const {
        return gb.read(0xFF40) & 0x04;
    }

    constexpr static uint16_t OAMStartAddress = 0xFE00;
    constexpr static uint8_t totalSprites = 40;
    constexpr static uint8_t bytesPerSprite = 4;

    //resets all values to that of a new frame
    void BeginNewFrame();

    struct Sprite {
        uint8_t x;
        uint8_t y;
        uint8_t tile;
        uint8_t flags;
    };

    Sprite spriteBuffer[10] = {};
    uint8_t nextEmptySlot{};
};



#endif