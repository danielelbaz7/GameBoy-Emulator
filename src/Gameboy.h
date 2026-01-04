#pragma once
#include <cstdint>
#include <set>
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
    Gameboy();

    void LoadRom(char const* filename);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t byteToWrite);
    void setFlag(unsigned char flagName, bool flagValue);
    bool readFlag(unsigned char flagName) const;

    bool stopped = false;

    uint8_t Step();
    std::vector<uint8_t> rom;

    void setOAMDisabled(const bool setTo) {
        isOAMDisabledByPPU = setTo;
    }

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

    //ime used to disable or enable all interrupts, IME=1/true is enabled, IME=0/false is disabled
    bool IME{}; //interrupt master enable flag

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

    //stores the current 16kb window we are storing in the bank and are able to look at
    uint8_t currentRomWindow = 1;

    // rom/ram select mode
    const uint8_t ROM_MODE = 0;
    const uint8_t RAM_MODE = 1;

    uint8_t bankModeToUse{ROM_MODE};

    void BuildOpcodeTables();

    bool halted = false;

    const uint8_t dotsPerMCycle{4};

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
    uint8_t OP_0xC3();
    uint8_t OP_0xC4();
    uint8_t OP_0xC5();
    uint8_t OP_0xC6();
    uint8_t OP_0xC7();
    uint8_t OP_0xC8();
    uint8_t OP_0xC9();
    uint8_t OP_0xCA();
    uint8_t OP_0xCC();
    uint8_t OP_0xCD();
    uint8_t OP_0xCE();
    uint8_t OP_0xCF();

    uint8_t OP_0xD0();
    uint8_t OP_0xD1();
    uint8_t OP_0xD2();
    uint8_t OP_0xD4();
    uint8_t OP_0xD5();
    uint8_t OP_0xD6();
    uint8_t OP_0xD7();
    uint8_t OP_0xD8();
    uint8_t OP_0xD9();
    uint8_t OP_0xDA();
    uint8_t OP_0xDC();
    uint8_t OP_0xDE();
    uint8_t OP_0xDF();

    uint8_t OP_0xE0();
    uint8_t OP_0xE1();
    uint8_t OP_0xE2();
    uint8_t OP_0xE5();
    uint8_t OP_0xE6();
    uint8_t OP_0xE7();
    uint8_t OP_0xE8();
    uint8_t OP_0xE9();
    uint8_t OP_0xEA();
    uint8_t OP_0xEE();
    uint8_t OP_0xEF();

    uint8_t OP_0xF0();
    uint8_t OP_0xF1();
    uint8_t OP_0xF2();
    uint8_t OP_0xF3();
    uint8_t OP_0xF5();
    uint8_t OP_0xF6();
    uint8_t OP_0xF7();
    uint8_t OP_0xF8();
    uint8_t OP_0xF9();
    uint8_t OP_0xFA();
    uint8_t OP_0xFB();
    uint8_t OP_0xFE();
    uint8_t OP_0xFF();

    uint8_t OP_NULL(); //function to point to if there is no opcode at that index. ex: 0xE3

    uint8_t OP_0xCB00();
    uint8_t OP_0xCB01();
    uint8_t OP_0xCB02();
    uint8_t OP_0xCB03();
    uint8_t OP_0xCB04();
    uint8_t OP_0xCB05();
    uint8_t OP_0xCB06();
    uint8_t OP_0xCB07();
    uint8_t OP_0xCB08();
    uint8_t OP_0xCB09();
    uint8_t OP_0xCB0A();
    uint8_t OP_0xCB0B();
    uint8_t OP_0xCB0C();
    uint8_t OP_0xCB0D();
    uint8_t OP_0xCB0E();
    uint8_t OP_0xCB0F();

    uint8_t OP_0xCB10();
    uint8_t OP_0xCB11();
    uint8_t OP_0xCB12();
    uint8_t OP_0xCB13();
    uint8_t OP_0xCB14();
    uint8_t OP_0xCB15();
    uint8_t OP_0xCB16();
    uint8_t OP_0xCB17();
    uint8_t OP_0xCB18();
    uint8_t OP_0xCB19();
    uint8_t OP_0xCB1A();
    uint8_t OP_0xCB1B();
    uint8_t OP_0xCB1C();
    uint8_t OP_0xCB1D();
    uint8_t OP_0xCB1E();
    uint8_t OP_0xCB1F();

    uint8_t OP_0xCB20();
    uint8_t OP_0xCB21();
    uint8_t OP_0xCB22();
    uint8_t OP_0xCB23();
    uint8_t OP_0xCB24();
    uint8_t OP_0xCB25();
    uint8_t OP_0xCB26();
    uint8_t OP_0xCB27();
    uint8_t OP_0xCB28();
    uint8_t OP_0xCB29();
    uint8_t OP_0xCB2A();
    uint8_t OP_0xCB2B();
    uint8_t OP_0xCB2C();
    uint8_t OP_0xCB2D();
    uint8_t OP_0xCB2E();
    uint8_t OP_0xCB2F();

    uint8_t OP_0xCB30();
    uint8_t OP_0xCB31();
    uint8_t OP_0xCB32();
    uint8_t OP_0xCB33();
    uint8_t OP_0xCB34();
    uint8_t OP_0xCB35();
    uint8_t OP_0xCB36();
    uint8_t OP_0xCB37();
    uint8_t OP_0xCB38();
    uint8_t OP_0xCB39();
    uint8_t OP_0xCB3A();
    uint8_t OP_0xCB3B();
    uint8_t OP_0xCB3C();
    uint8_t OP_0xCB3D();
    uint8_t OP_0xCB3E();
    uint8_t OP_0xCB3F();

    uint8_t OP_0xCB40();
    uint8_t OP_0xCB41();
    uint8_t OP_0xCB42();
    uint8_t OP_0xCB43();
    uint8_t OP_0xCB44();
    uint8_t OP_0xCB45();
    uint8_t OP_0xCB46();
    uint8_t OP_0xCB47();
    uint8_t OP_0xCB48();
    uint8_t OP_0xCB49();
    uint8_t OP_0xCB4A();
    uint8_t OP_0xCB4B();
    uint8_t OP_0xCB4C();
    uint8_t OP_0xCB4D();
    uint8_t OP_0xCB4E();
    uint8_t OP_0xCB4F();

    uint8_t OP_0xCB50();
    uint8_t OP_0xCB51();
    uint8_t OP_0xCB52();
    uint8_t OP_0xCB53();
    uint8_t OP_0xCB54();
    uint8_t OP_0xCB55();
    uint8_t OP_0xCB56();
    uint8_t OP_0xCB57();
    uint8_t OP_0xCB58();
    uint8_t OP_0xCB59();
    uint8_t OP_0xCB5A();
    uint8_t OP_0xCB5B();
    uint8_t OP_0xCB5C();
    uint8_t OP_0xCB5D();
    uint8_t OP_0xCB5E();
    uint8_t OP_0xCB5F();

    uint8_t OP_0xCB60();
    uint8_t OP_0xCB61();
    uint8_t OP_0xCB62();
    uint8_t OP_0xCB63();
    uint8_t OP_0xCB64();
    uint8_t OP_0xCB65();
    uint8_t OP_0xCB66();
    uint8_t OP_0xCB67();
    uint8_t OP_0xCB68();
    uint8_t OP_0xCB69();
    uint8_t OP_0xCB6A();
    uint8_t OP_0xCB6B();
    uint8_t OP_0xCB6C();
    uint8_t OP_0xCB6D();
    uint8_t OP_0xCB6E();
    uint8_t OP_0xCB6F();

    uint8_t OP_0xCB70();
    uint8_t OP_0xCB71();
    uint8_t OP_0xCB72();
    uint8_t OP_0xCB73();
    uint8_t OP_0xCB74();
    uint8_t OP_0xCB75();
    uint8_t OP_0xCB76();
    uint8_t OP_0xCB77();
    uint8_t OP_0xCB78();
    uint8_t OP_0xCB79();
    uint8_t OP_0xCB7A();
    uint8_t OP_0xCB7B();
    uint8_t OP_0xCB7C();
    uint8_t OP_0xCB7D();
    uint8_t OP_0xCB7E();
    uint8_t OP_0xCB7F();

    uint8_t OP_0xCB80();
    uint8_t OP_0xCB81();
    uint8_t OP_0xCB82();
    uint8_t OP_0xCB83();
    uint8_t OP_0xCB84();
    uint8_t OP_0xCB85();
    uint8_t OP_0xCB86();
    uint8_t OP_0xCB87();
    uint8_t OP_0xCB88();
    uint8_t OP_0xCB89();
    uint8_t OP_0xCB8A();
    uint8_t OP_0xCB8B();
    uint8_t OP_0xCB8C();
    uint8_t OP_0xCB8D();
    uint8_t OP_0xCB8E();
    uint8_t OP_0xCB8F();

    uint8_t OP_0xCB90();
    uint8_t OP_0xCB91();
    uint8_t OP_0xCB92();
    uint8_t OP_0xCB93();
    uint8_t OP_0xCB94();
    uint8_t OP_0xCB95();
    uint8_t OP_0xCB96();
    uint8_t OP_0xCB97();
    uint8_t OP_0xCB98();
    uint8_t OP_0xCB99();
    uint8_t OP_0xCB9A();
    uint8_t OP_0xCB9B();
    uint8_t OP_0xCB9C();
    uint8_t OP_0xCB9D();
    uint8_t OP_0xCB9E();
    uint8_t OP_0xCB9F();

    uint8_t OP_0xCBA0();
    uint8_t OP_0xCBA1();
    uint8_t OP_0xCBA2();
    uint8_t OP_0xCBA3();
    uint8_t OP_0xCBA4();
    uint8_t OP_0xCBA5();
    uint8_t OP_0xCBA6();
    uint8_t OP_0xCBA7();
    uint8_t OP_0xCBA8();
    uint8_t OP_0xCBA9();
    uint8_t OP_0xCBAA();
    uint8_t OP_0xCBAB();
    uint8_t OP_0xCBAC();
    uint8_t OP_0xCBAD();
    uint8_t OP_0xCBAE();
    uint8_t OP_0xCBAF();

    uint8_t OP_0xCBB0();
    uint8_t OP_0xCBB1();
    uint8_t OP_0xCBB2();
    uint8_t OP_0xCBB3();
    uint8_t OP_0xCBB4();
    uint8_t OP_0xCBB5();
    uint8_t OP_0xCBB6();
    uint8_t OP_0xCBB7();
    uint8_t OP_0xCBB8();
    uint8_t OP_0xCBB9();
    uint8_t OP_0xCBBA();
    uint8_t OP_0xCBBB();
    uint8_t OP_0xCBBC();
    uint8_t OP_0xCBBD();
    uint8_t OP_0xCBBE();
    uint8_t OP_0xCBBF();

    uint8_t OP_0xCBC0();
    uint8_t OP_0xCBC1();
    uint8_t OP_0xCBC2();
    uint8_t OP_0xCBC3();
    uint8_t OP_0xCBC4();
    uint8_t OP_0xCBC5();
    uint8_t OP_0xCBC6();
    uint8_t OP_0xCBC7();
    uint8_t OP_0xCBC8();
    uint8_t OP_0xCBC9();
    uint8_t OP_0xCBCA();
    uint8_t OP_0xCBCB();
    uint8_t OP_0xCBCC();
    uint8_t OP_0xCBCD();
    uint8_t OP_0xCBCE();
    uint8_t OP_0xCBCF();

    uint8_t OP_0xCBD0();
    uint8_t OP_0xCBD1();
    uint8_t OP_0xCBD2();
    uint8_t OP_0xCBD3();
    uint8_t OP_0xCBD4();
    uint8_t OP_0xCBD5();
    uint8_t OP_0xCBD6();
    uint8_t OP_0xCBD7();
    uint8_t OP_0xCBD8();
    uint8_t OP_0xCBD9();
    uint8_t OP_0xCBDA();
    uint8_t OP_0xCBDB();
    uint8_t OP_0xCBDC();
    uint8_t OP_0xCBDD();
    uint8_t OP_0xCBDE();
    uint8_t OP_0xCBDF();

    uint8_t OP_0xCBE0();
    uint8_t OP_0xCBE1();
    uint8_t OP_0xCBE2();
    uint8_t OP_0xCBE3();
    uint8_t OP_0xCBE4();
    uint8_t OP_0xCBE5();
    uint8_t OP_0xCBE6();
    uint8_t OP_0xCBE7();
    uint8_t OP_0xCBE8();
    uint8_t OP_0xCBE9();
    uint8_t OP_0xCBEA();
    uint8_t OP_0xCBEB();
    uint8_t OP_0xCBEC();
    uint8_t OP_0xCBED();
    uint8_t OP_0xCBEE();
    uint8_t OP_0xCBEF();

    uint8_t OP_0xCBF0();
    uint8_t OP_0xCBF1();
    uint8_t OP_0xCBF2();
    uint8_t OP_0xCBF3();
    uint8_t OP_0xCBF4();
    uint8_t OP_0xCBF5();
    uint8_t OP_0xCBF6();
    uint8_t OP_0xCBF7();
    uint8_t OP_0xCBF8();
    uint8_t OP_0xCBF9();
    uint8_t OP_0xCBFA();
    uint8_t OP_0xCBFB();
    uint8_t OP_0xCBFC();
    uint8_t OP_0xCBFD();
    uint8_t OP_0xCBFE();
    uint8_t OP_0xCBFF();
    
    using OpcodeFunction = uint8_t (Gameboy::*) ();
    OpcodeFunction opcodeTable[256]{};
    OpcodeFunction CBopcodeTable[256]{};

    bool isOAMDisabledByPPU{};

};
