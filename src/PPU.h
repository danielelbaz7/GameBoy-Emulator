#ifndef GAMEBOYEMULATOR_PPU_H
#define GAMEBOYEMULATOR_PPU_H
#include "CPU.h"

enum class PPUMode : uint8_t {
        HBlank = 0,
        VBlank = 1,
        OAM    = 2,
        Draw   = 3
    };
    //then mode 0 is horizontal blank, and mode 1 is vertical blank


class PPU {

public:
    explicit PPU(Memory& m);
    void UpdatePPU(uint8_t TcyclesSinceLastUpdate);
    PPUMode currentMode{PPUMode::OAM};
    

private:

    uint8_t Read(uint16_t address) const { return mem.Read(address, MemoryAccessor::PPU); }
    uint32_t frameBuffer[144][160] = {};

    Memory& mem;
    unsigned int TcyclesSinceLastScanline{};
    uint8_t currentScanline{}; //goes from 0-153, last 10 are vblank
    
    

    //lambda function that returns the current sprite height at any point
    [[nodiscard]] uint8_t spriteHeight() const { return Read(0xFF40) & 0x04; }

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