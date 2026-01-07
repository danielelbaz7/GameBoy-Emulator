#ifndef GAMEBOYEMULATOR_PPU_H
#define GAMEBOYEMULATOR_PPU_H
#include <cstdint>
#include "Memory.h"

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
    uint32_t frameBuffer[144][160]{};

    Memory& mem;
    unsigned int TcyclesSinceLastScanline{};
    uint8_t currentScanline{}; //goes from 0-153, last 10 are vblank
    uint8_t windowLinesWritten{};

    void DrawBackground(uint32_t *scanline, uint8_t *bgWindowScanline);
    void DrawWindow(uint32_t *scanline, uint8_t *bgWindowScanline);
    void DrawSprites(uint32_t *scanline, uint8_t *bgWindowScanline);

    [[nodiscard]] bool spritesEnabled() const { return ((((Read(0xFF40) & 0x02) >> 1u) == 1) ? true : false); }
    //lambda function that returns the current sprite height at any point
    [[nodiscard]] uint8_t spriteHeight() const { return ((Read(0xFF40) & 0x04) >> 2u == 1) ? 16 : 8; }
    //checks bit 3, to tell bg which address to use
    [[nodiscard]] bool LCDCBit3Tilemaps() const { return (((Read(0xFF40) & 0x08) >> 3u) == 1) ? true : false; }
    [[nodiscard]] bool windowEnabled() const { return ((((Read(0xFF40) & 0x20) >> 5u) == 1) ? true : false); }
    [[nodiscard]] uint8_t windowStartY() const { return Read(0xFF4A); }
    [[nodiscard]] uint8_t windowStartX() const { return Read(0xFF4B); }
    //same as lcdcbit3 tilemaps, just for window
    [[nodiscard]] bool LCDCBit6Tilemaps() const { return (((Read(0xFF40) & 0x40) >> 6u) == 1) ? true : false; }


    constexpr static uint16_t OAMStartAddress = 0xFE00;
    constexpr static uint8_t totalSprites = 40;
    constexpr static uint8_t bytesPerSprite = 4;

    struct Sprite {
        uint8_t y;
        uint8_t x;
        uint8_t tile;
        uint8_t flags;
        uint8_t OAMIndex;
    };

    bool SpriteFlagBitValue(const Sprite &s, uint8_t bit) {
        return (s.flags & (0x01 << bit)) == 0 ? false : true;
    }

    Sprite spriteBuffer[10] = {};
    uint8_t nextEmptySlot{};

};

#endif