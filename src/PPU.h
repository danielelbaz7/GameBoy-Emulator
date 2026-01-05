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
    uint32_t* getFrameBuffer() { return *frameBuffer; };
    uint16_t getColCount() { return (sizeof(frameBuffer[0]) / 4); }

private:
    const uint32_t colors[4] = {
        0xF2FBFFFF,  // very light blue
        0xA9D8FFFF,  // light blue
        0x3B82C4FF,  // medium blue
        0x0B1D39FF   // deep navy
    };
    uint8_t Read(uint16_t address) const { return mem.Read(address, MemoryAccessor::PPU); }
    uint32_t frameBuffer[144][160] = {};

    Memory& mem;
    unsigned int TcyclesSinceLastScanline{};
    uint8_t currentScanline{}; //goes from 0-153, last 10 are vblank
    
    

    //lambda function that returns the current sprite height at any point
    [[nodiscard]] uint8_t spriteHeight() const { return ((Read(0xFF40) & 0x04) >> 2u == 1) ? 16 : 8; }
    [[nodiscard]] uint8_t currentTileMap() const { return ((Read(0xFF40) & 0x08) >> 3u); }

    constexpr static uint16_t OAMStartAddress = 0xFE00;
    constexpr static uint8_t totalSprites = 40;
    constexpr static uint8_t bytesPerSprite = 4;

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