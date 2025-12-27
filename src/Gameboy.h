#pragma once
#include <cstdint>
#include <vector>


union af{
    uint16_t reg16;
    struct {
        uint8_t f;
        uint8_t a;
    };
};

union bc{
    uint16_t reg16;
    struct {
        uint8_t c;
        uint8_t b;
    };
};

union de{
    uint16_t reg16;
    struct {
        uint8_t e;
        uint8_t d;
    };
};

union hl{
    uint16_t reg16;
    struct {
        uint8_t l;
        uint8_t h;
    };
};



class Gameboy {
    
public:
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t byteToWrite);
    void setFlag(char flagName, bool flagValue);

    bool readFlag(char flagName) const;

private:
    // CPU Registers
    // Uses union to store the pairs as both 8-bit and 16-bit registers (in the same memory location)
    // Ex. bc.reg16 = 0x1234; bc.b = bc's high value = 0x12; bc.c = bc's low value = 0x34;
    // initialize to their default values after the boot rom
    af af{0x01B0};
    bc bc{0x0013};
    de de{0x00D8};
    hl hl{0x014D};

    uint16_t sp{0xFFFE}; //stack pointer, initialized to highest bit of high ram
    uint16_t pc{0x0100}; //program counter

    // Flag bits in the F register (lower byte of AF)
    const uint8_t FLAG_Z = 0x80; // 1000 0000
    const uint8_t FLAG_N = 0x40; // 0100 0000
    const uint8_t FLAG_H = 0x20; // 0010 0000
    const uint8_t FLAG_C = 0x10; // 0001 0000


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
    std::vector<uint8_t> rom;
    //stores the current 16kb window we are storing in the bank and are able to look at
    uint8_t currentRomWindow = 1;

    // rom/ram select mode
    const uint8_t ROM_MODE = 0;
    const uint8_t RAM_MODE = 1;

    uint8_t bankModeToUse{ROM_MODE};


    uint8_t registers [0x08]{};

    void LoadRom(char const* filename);

    //opcode functions
    uint8_t OP_0x00();
    uint8_t OP_0x01();
    uint8_t OP_0x02();
    uint8_t OP_0x03();
    uint8_t OP_0x04();
    uint8_t OP_0x05();
    uint8_t OP_0x06();
    uint8_t OP_0x07();
        

};
