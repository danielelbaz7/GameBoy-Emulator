//
// Created by Daniel Elbaz on 1/4/26.
//
#ifndef GAMEBOYEMULATOR_MEMORY_H
#define GAMEBOYEMULATOR_MEMORY_H
#include <vector>
#include <array>
#include <cstdint>
#include <unordered_map>

enum class PPUMode : uint8_t {
    HBlank = 0,
    VBlank = 1,
    OAM    = 2,
    Draw   = 3
};

enum class MemoryAccessor { CPU, PPU };
enum class KeyStatus : bool { Pressed = false, Released = true };

class Memory {
public:
    void LoadRom(char const* filename);
    void InitializeMemory();

    void WriteScanline(uint8_t value, MemoryAccessor caller);
    std::array<uint8_t, 16> ReadTile(uint8_t tileID, MemoryAccessor caller = MemoryAccessor::PPU);
    std::array<uint8_t, 16> ReadSpriteTile(uint8_t tileID, MemoryAccessor caller = MemoryAccessor::PPU);
    uint8_t Read(uint16_t address, MemoryAccessor caller = MemoryAccessor::CPU);
    void Write(uint16_t address, uint8_t byteToWrite, MemoryAccessor caller = MemoryAccessor::CPU);
    void setMode(PPUMode newMode);
    void WriteCoincidence(bool LYEqualsLYC);
    void UpdateCounter(uint8_t TcyclesSinceLastInstr);
    void UpdateTIMA(uint16_t oldCounter, uint16_t newCounter);
    void SetJoypadInterrupt();
    void SetButtonStatus(std::unordered_map<std::string, KeyStatus> &buttonStatusRef) { buttonStatus = &buttonStatusRef; };


private:
    // set to default mode (VBlank)
    PPUMode mode = PPUMode::VBlank;
    bool isLcdOn();

    // All addresses/memory available to the Gameboy, 16-bit addresses
    // Video Memory (VRAM): 8000-9FFF (8KB)
    uint8_t vram[0x2000]{};
    // Work ram bank 0: C000-CFFF (4KB)
    // Work ram bank 1: D000-DFFF (4KB)
    // High ram: FF80-FFFE (127B)
    // Sprite Attribute Table: FE00-FE9F (160B)
    // I/O Registers: FF00-FF7F (128B)
    //work ram, no banking in the original gameboy, only the gameboy color which we are not implementing
    uint8_t wram[0x2000]{};


    uint8_t oam[0xA0]{}; //object attribute memory, stores up to 40 sprites, 160 bytes
    uint8_t io[0x80]{}; //input output ports, stores data about different physical pieces of the gameboy (like buttons)
    uint8_t hram[0x7F]{}; //close to cpu, small amt of memory, fast
    std::vector<uint8_t> rom;
    uint8_t ieReg{}; //interrupt enable register, only 5 bits used, stores what hardware events can interrupt cpu

    //there is also some forbidden and unused memory we do not have implemented

    //--CARTRIDGE--

    // External RAM, can be a lot more than 8KB but we can only see (8KB) at a time, used for save files (.sav)
    std::vector<uint8_t> eRam;

    //this controls whether eram is enabled for reading and writing. this was physically stored, not a memory
    //address in the original gameboy. if you try to write to the first 8192 addresses in memory, we detect that
    //as enabling/disabling eram depending on the value
    bool eRamEnabled = false;

    //used for external RAM banking
    uint8_t currentERamWindow = 0;

    // Memory banks for ROM (16KB each)
    //0000-3FFF
    //4000-7FFF this bank is a sliding window
    // We store the entire ROM data but can only access it in two banks, this is the entire ROM data in bytes

    //stores the current 16kb window we are storing in the bank and are able to look at
    uint8_t currentRomWindow = 1;

    // rom/ram select mode
    const uint8_t ROM_MODE = 0;
    const uint8_t RAM_MODE = 1;

    uint8_t bankModeToUse{ROM_MODE};

    uint16_t internalCounter{};

    uint16_t TACValues[4]{1024, 16, 64, 256};

    uint8_t selectedGroup{0x30}; // 0x30 means no group selected, 0x20 is direction (WASD)
    //0x10 is action buttons, 0x00 is both groups selected
    std::unordered_map<std::string, KeyStatus> *buttonStatus = nullptr;
    uint8_t SetJoypadBits();

};


#endif //GAMEBOYEMULATOR_MEMORY_H