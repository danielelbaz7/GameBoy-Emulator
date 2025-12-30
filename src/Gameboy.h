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
    void setFlag(unsigned char flagName, bool flagValue);

    bool readFlag(unsigned char flagName) const;

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
    uint8_t OP_0x08();
    uint8_t OP_0x09();
    uint8_t OP_0x0A();
    uint8_t OP_0x0B();
    uint8_t OP_0x0C();
    uint8_t OP_0x0D();
    uint8_t OP_0x0E();
    uint8_t OP_0x0F();

    uint8_t OP_0x10();
    uint8_t OP_0x11();
    uint8_t OP_0x12();
    uint8_t OP_0x13();
    uint8_t OP_0x14();
    uint8_t OP_0x15();
    uint8_t OP_0x16();
    uint8_t OP_0x17();
    uint8_t OP_0x18();
    uint8_t OP_0x19();
    uint8_t OP_0x1A();
    uint8_t OP_0x1B();
    uint8_t OP_0x1C();
    uint8_t OP_0x1D();
    uint8_t OP_0x1E();
    uint8_t OP_0x1F();
    
    uint8_t OP_0x20();
    uint8_t OP_0x21();
    uint8_t OP_0x22();
    uint8_t OP_0x23();
    uint8_t OP_0x24();
    uint8_t OP_0x25();
    uint8_t OP_0x26();
    uint8_t OP_0x27();
    uint8_t OP_0x28();
    uint8_t OP_0x29();
    uint8_t OP_0x2A();
    uint8_t OP_0x2B();
    uint8_t OP_0x2C();
    uint8_t OP_0x2D();
    uint8_t OP_0x2E();
    uint8_t OP_0x2F();

    uint8_t OP_0x30();
    uint8_t OP_0x31();
    uint8_t OP_0x32();
    uint8_t OP_0x33();
    uint8_t OP_0x34();
    uint8_t OP_0x35();
    uint8_t OP_0x36();
    uint8_t OP_0x37();
    uint8_t OP_0x38();
    uint8_t OP_0x39();
    uint8_t OP_0x3A();
    uint8_t OP_0x3B();
    uint8_t OP_0x3C();
    uint8_t OP_0x3D();
    uint8_t OP_0x3E();
    uint8_t OP_0x3F();

    uint8_t OP_0x40();
    uint8_t OP_0x41();
    uint8_t OP_0x42();
    uint8_t OP_0x43();
    uint8_t OP_0x44();
    uint8_t OP_0x45();
    uint8_t OP_0x46();
    uint8_t OP_0x47();
    uint8_t OP_0x48();
    uint8_t OP_0x49();
    uint8_t OP_0x4A();
    uint8_t OP_0x4B();
    uint8_t OP_0x4C();
    uint8_t OP_0x4D();
    uint8_t OP_0x4E();
    uint8_t OP_0x4F();

    uint8_t OP_0x50();
    uint8_t OP_0x51();
    uint8_t OP_0x52();
    uint8_t OP_0x53();
    uint8_t OP_0x54();
    uint8_t OP_0x55();
    uint8_t OP_0x56();
    uint8_t OP_0x57();
    uint8_t OP_0x58();
    uint8_t OP_0x59();
    uint8_t OP_0x5A();
    uint8_t OP_0x5B();
    uint8_t OP_0x5C();
    uint8_t OP_0x5D();
    uint8_t OP_0x5E();
    uint8_t OP_0x5F();

    uint8_t OP_0x60();
    uint8_t OP_0x61();
    uint8_t OP_0x62();
    uint8_t OP_0x63();
    uint8_t OP_0x64();
    uint8_t OP_0x65();
    uint8_t OP_0x66();
    uint8_t OP_0x67();
    uint8_t OP_0x68();
    uint8_t OP_0x69();
    uint8_t OP_0x6A();
    uint8_t OP_0x6B();
    uint8_t OP_0x6C();
    uint8_t OP_0x6D();
    uint8_t OP_0x6E();
    uint8_t OP_0x6F();

    uint8_t OP_0x70();
    uint8_t OP_0x71();
    uint8_t OP_0x72();
    uint8_t OP_0x73();
    uint8_t OP_0x74();
    uint8_t OP_0x75();
    uint8_t OP_0x76();
    uint8_t OP_0x77();
    uint8_t OP_0x78();
    uint8_t OP_0x79();
    uint8_t OP_0x7A();
    uint8_t OP_0x7B();
    uint8_t OP_0x7C();
    uint8_t OP_0x7D();
    uint8_t OP_0x7E();
    uint8_t OP_0x7F();

    uint8_t OP_0x80();
    uint8_t OP_0x81();
    uint8_t OP_0x82();
    uint8_t OP_0x83();
    uint8_t OP_0x84();
    uint8_t OP_0x85();
    uint8_t OP_0x86();
    uint8_t OP_0x87();
    uint8_t OP_0x88();
    uint8_t OP_0x89();
    uint8_t OP_0x8A();
    uint8_t OP_0x8B();
    uint8_t OP_0x8C();
    uint8_t OP_0x8D();
    uint8_t OP_0x8E();
    uint8_t OP_0x8F();

    uint8_t OP_0x90();
    uint8_t OP_0x91();
    uint8_t OP_0x92();
    uint8_t OP_0x93();
    uint8_t OP_0x94();
    uint8_t OP_0x95();
    uint8_t OP_0x96();
    uint8_t OP_0x97();
    uint8_t OP_0x98();
    uint8_t OP_0x99();
    uint8_t OP_0x9A();
    uint8_t OP_0x9B();
    uint8_t OP_0x9C();
    uint8_t OP_0x9D();
    uint8_t OP_0x9E();
    uint8_t OP_0x9F();

    uint8_t OP_0xA0();
    uint8_t OP_0xA1();
    uint8_t OP_0xA2();
    uint8_t OP_0xA3();
    uint8_t OP_0xA4();
    uint8_t OP_0xA5();
    uint8_t OP_0xA6();
    uint8_t OP_0xA7();
    uint8_t OP_0xA8();
    uint8_t OP_0xA9();
    uint8_t OP_0xAA();
    uint8_t OP_0xAB();
    uint8_t OP_0xAC();
    uint8_t OP_0xAD();
    uint8_t OP_0xAE();
    uint8_t OP_0xAF();

    uint8_t OP_0xB0();
    uint8_t OP_0xB1();
    uint8_t OP_0xB2();
    uint8_t OP_0xB3();
    uint8_t OP_0xB4();
    uint8_t OP_0xB5();
    uint8_t OP_0xB6();
    uint8_t OP_0xB7();
    uint8_t OP_0xB8();
    uint8_t OP_0xB9();
    uint8_t OP_0xBA();
    uint8_t OP_0xBB();
    uint8_t OP_0xBC();
    uint8_t OP_0xBD();
    uint8_t OP_0xBE();
    uint8_t OP_0xBF();

    uint8_t OP_0xC0();

    uint8_t OP_0xC1();

    uint8_t OP_0xC2();
};
