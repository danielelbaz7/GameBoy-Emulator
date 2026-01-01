#include <vector>
#include <fstream>
#include <iostream>
#include "./Gameboy.h"

#include "OpcodeHelpers.h"

uint8_t Gameboy::read(uint16_t address) {
    if (address <= 0x3FFF) {
        return rom[address];
    }

    if (address <= 0x7FFF) {
        //return the rom at the current window. since the address is greater than 16KB, subtract 16KB from the address
        //this makes address basically equal to the local location inside of the bank
        return rom[((currentRomWindow) * 0x4000) + (address - 0x4000)];
    }

    if (address <= 0x9FFF) {
        //subtract 0x8000 for the vram offset
        return vram[address - 0x8000];
    }

    if (address <= 0xBFFF) {
        //return the value in external ram only if eRam is enabled
        return eRamEnabled ? eRam[(currentERamWindow * 0x2000) + (address - 0xA000)] : 0xFF;
    }

    if (address <= 0xDFFF) {
        //work ram, banking is irrelevant here
        return wram[address - 0xC000];
    }

    if (address <= 0xFDFF) {
        //this mirrors the workram, subtract its offset
        return wram[address - 0xE000];
    }

    if (address <= 0xFE9F) {
        //sprite memory
        return oam[address - 0xFE00];
    }

    if (address <= 0xFEFF) {
        //not usable memory, return 255, data bus defaults to HIGH in cases like this (unmapped/unusable mem)
        return 0xFF;
    }

    if (address <= 0xFF7F) {
        //io port
        return io[address - 0xFF00];
    }

    if (address <= 0xFFFE) {
        //high ram
        return hram[address - 0xFF80];
    }

    if (address == 0xFFFF) {
        return ieReg;
    }

    return 0xFF;

}

void Gameboy::write(uint16_t address, uint8_t byteToWrite) {
    //handles eram disable/enable
    if (address <= 0x1FFF) {
        //takes only the lower 4 bits of the byte we are writing
        uint8_t lower4Bits = (byteToWrite & 0x0F);
        //if the lower 4 bits are A, enable eRam. else, disable it
        if (lower4Bits == 0x0A) {
            eRamEnabled = true;
        } else {
            eRamEnabled = false;
        }
        return;
    }
    // handles rom bank switching & validation
    if (address <= 0x3FFF) {
        uint8_t lower5Bits = (byteToWrite & 0x1F);
        if (lower5Bits == 0x00) {
            lower5Bits = 0x01;
        }
        currentRomWindow = (currentRomWindow & ~0x1Fu) | lower5Bits;
        return;
    }
    
    if (address <= 0x5FFF) {
        if(bankModeToUse == ROM_MODE) {
            //set bits 5 and 6 to the two bits in the register, then shift left so its bits 5 and 6
            uint8_t romBankToUse = ((byteToWrite & 0x03) << 5u);
            currentRomWindow = (currentRomWindow & ~0x60u) | romBankToUse;
        } else {
            //set the ram window to the 2 bits in this register
            uint8_t ramBankToUse = (byteToWrite & 0x03);
            currentERamWindow = (currentERamWindow & ~0x03u) | ramBankToUse;
        }
        return;
    }

    //decide whether we are using rom or ram mode
    if (address <= 0x7FFF) {
        uint8_t lower4Bits = (byteToWrite & 0x0F);
        //ram mode is 1, rom mode is 0
        lower4Bits == RAM_MODE ? bankModeToUse = RAM_MODE : bankModeToUse = ROM_MODE;
        return;
    }
    
    if (address <= 0xBFFF) {
        //if the cartridge has no ram, the external ram is just disabled by default and should never modified
        if(eRamEnabled) {
            eRam[(currentERamWindow * 0x2000) + (address - 0xA000)] = byteToWrite;
        }
        return;
    }

    if (address <= 0xDFFF) {
        wram[address - 0xC000] = byteToWrite;
        return;
    }

    if (address <= 0xFDFF) {
        wram[address - 0xE000] = byteToWrite;
        return;
    }

    if (address <= 0xFE9F) {
        oam[address - 0xFE00] = byteToWrite;
        return;
    }

    if (address <= 0xFEFF) {
        return;
    }

    if (address <= 0xFF7F) {
        io[address - 0xFF00] = byteToWrite;
        return;
    }

    if (address <= 0xFFFE) {
        hram[address - 0xFF80] = byteToWrite;
        return;
    }
    
    if (address == 0xFFFF) {
        ieReg = byteToWrite;
        return;
    }

}

// Run function
void Gameboy::run() {
    if (stopped) {
        // dont do shit
        // check for restart indicators
        return;
    }
    if (halted) {
        // do everything but pc increment and read instruction (no cpu things)
        // update other timers
        return;
    }
    cycle();

    return;
}

// Cycle function
void Gameboy::cycle() {
    // get opcode
    // run opcode function
    // increment pc++
    uint8_t opcode = read(pc);
    
    //95
    //1001 0101
    //*opcodeTable[1001][0101]();
    
    pc++;
    return;
}


//flag setting
// added breaks and '&=' instead of just '&'
void Gameboy::setFlag(unsigned char flagName, bool flagValue) {
    switch (flagName) {
        case 'Z':
            flagValue ? af.f |= (FLAG_Z) : af.f &= ~FLAG_Z;
            break;
        case 'N':
            flagValue ? af.f |= (FLAG_N) : af.f &= ~FLAG_N;
            break;
        case 'H':
            flagValue ? af.f |= (FLAG_H) : af.f &= ~FLAG_H;
            break;
        case 'C':
            flagValue ? af.f |= (FLAG_C) : af.f &= ~FLAG_C;
            break;
        default: break;
    }
}

bool Gameboy::readFlag(unsigned char flagName) const {
    switch (flagName) {
        case 'Z':
            //if the whole thing is 0, that means the flag is zero so we can return false
            //if it isnt zero, the flag is not zero so we return true
            return (af.f & (FLAG_Z)) != 0;
        case 'N':
            return (af.f & (FLAG_N)) != 0;
        case 'H':
            return (af.f & (FLAG_H)) != 0;
        case 'C':
            return (af.f & (FLAG_C)) != 0;
        default: return false;;
    }
}


//rom loading function

void Gameboy::LoadRom(char const* filename) {
    //create an input file stream that beings at the end, get the size, read into the vector 
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if(file.is_open()) {
        std::streampos filesize = file.tellg();
        if(filesize == -1) {
            std::cout << "Invalid Rom" << std::endl;
        }
        file.seekg(0, std::ios::beg);
        rom.resize(filesize);
        file.read(reinterpret_cast<char*>(rom.data()), filesize);
    }
}

// OPCODES

// OP_[ROW][COLUMN]
// Ex. x7 (row) xA (column) = OP_0x7A

uint8_t Gameboy::OP_0x00() {
    return 1;
}

//Load the 2 bytes of immediate data into register pair BC.
uint8_t Gameboy::OP_0x01() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    bc.reg16 = (highByte << 8u) | lowByte;
    return 3;
}

//Store the contents of register A in the memory location specified by register pair BC.
uint8_t Gameboy::OP_0x02() {
    write(bc.reg16, af.a);
    return 2;
}

//Increment the contents of register pair BC by 1.
uint8_t Gameboy::OP_0x03() {
    bc.reg16++;
    return 2;
}

//Increment the contents of register B by 1.
uint8_t Gameboy::OP_0x04(){
    uint8_t old = bc.b;
    bc.b++;
    setFlag('Z', bc.b==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register B by 1.
uint8_t Gameboy::OP_0x05(){
    uint8_t old = bc.b;
    bc.b--;
    setFlag('Z', bc.b==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register B.
uint8_t Gameboy::OP_0x06(){
    bc.b = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the left
uint8_t Gameboy::OP_0x07() {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (af.a & 0x80) >> 7u;
    //shift left
    af.a = af.a << 1u;
    //set bit 0 to old bit 7
    af.a |= oldBit7;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit7 == 0x01);

    return 1;
}

//Store lower byte of SP in address of 16bit immediate, higher in imm+1
uint8_t Gameboy::OP_0x08() {
    uint8_t spLower = (sp & 0x00FF);
    write(++pc, spLower);
    uint8_t spHigher = (sp & 0xFF00) >> 8u;
    write(++pc, spHigher);
    return 5;
}

//stores hl + bc in hl
uint8_t Gameboy::OP_0x09() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 = oldHl + bc.reg16;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (bc.reg16 & 0x0FFF)) > 0x0FFF);
    setFlag('C', (oldHl + bc.reg16) > 0xFFFF);
    return 2;
}

//store memory[bc] in a
uint8_t Gameboy::OP_0x0A() {
    af.a = read(bc.reg16);
    return 2;
}

//decrement bc by 1
uint8_t Gameboy::OP_0x0B() {
    bc.reg16--;
    return 2;
}

//increment register c by 1
uint8_t Gameboy::OP_0x0C() {
    uint8_t old = bc.c;
    bc.c++;
    setFlag('Z', bc.c == 0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register C by 1.
uint8_t Gameboy::OP_0x0D(){
    uint8_t old = bc.c;
    bc.c--;
    setFlag('Z', bc.c==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into c
uint8_t Gameboy::OP_0x0E(){
    bc.c = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the right
uint8_t Gameboy::OP_0x0F() {
    uint8_t oldBit0 = (af.a & 0x01) << 7u;
    af.a = af.a >> 1u;
    af.a |= oldBit0;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit0 == 0x80);

    return 1;
}

//STOP FUNCTION
// when exiting 'stop', incremement pc twice because two byte instruction ( 0x 10 00)
uint8_t Gameboy::OP_0x10() {
    stopped = true;
    return 1;
}

//load the next two bytes into de
uint8_t Gameboy::OP_0x11() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    de.reg16 = (highByte << 8u) | lowByte;
    return 3;
}

//store contents of register a in memory location specified by de
uint8_t Gameboy::OP_0x12() {
    uint16_t memoryLocation = de.reg16;
    write(memoryLocation, af.a);
    return 2;
}

//Increment the contents of register pair DE by 1.
uint8_t Gameboy::OP_0x13() {
    de.reg16++;
    return 2;
}

//Increment the contents of register D by 1.
uint8_t Gameboy::OP_0x14(){
    uint8_t old = de.d;
    de.d++;
    setFlag('Z', de.d==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register D by 1.
uint8_t Gameboy::OP_0x15(){
    uint8_t old = de.d;
    de.d--;
    setFlag('Z', de.d==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into d
uint8_t Gameboy::OP_0x16(){
    de.d = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the left through the carry flag
uint8_t Gameboy::OP_0x17() {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (af.a & 0x80) >> 7u;
    //shift left
    af.a = af.a << 1u;
    //set bit 0 to carry flag
    af.a |= ((af.f & FLAG_C) >> 4u);

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit7 == 0x01);

    return 1;
}

//Jump s8 steps from the current address in the program counter (PC). (Jump relative.)
uint8_t Gameboy::OP_0x18() {
    pc++;
    auto jumpSteps = static_cast<int8_t>(read(++pc));
    pc += jumpSteps;
    // adjust for the automatic pc increment after opcode function
    pc--;
    return 3;
}

// Add the contents of register pair DE to the contents of register pair HL, and store the results in register pair HL.
uint8_t Gameboy::OP_0x19() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 += de.reg16;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (de.reg16 & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHl) + static_cast<uint32_t>(de.reg16)) > 0xFFFF);
    return 2;
}

//Load the 8-bit contents of memory specified by register pair DE into register A.
uint8_t Gameboy::OP_0x1A() {
    af.a = read(de.reg16);
    return 2;
}

//decrement de by 1
uint8_t Gameboy::OP_0x1B() {
    de.reg16--;
    return 2;
}

//increment register e's contents by 1
uint8_t Gameboy::OP_0x1C(){
    uint8_t old = de.e;
    de.e++;
    setFlag('Z', de.e==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register e by 1.
uint8_t Gameboy::OP_0x1D(){
    uint8_t old = de.e;
    de.e--;
    setFlag('Z', de.e==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into e
uint8_t Gameboy::OP_0x1E(){
    de.e = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the right through the carry flag
uint8_t Gameboy::OP_0x1F() {
    //gets old 0 bit
    uint8_t oldBit0 = (af.a & 0x01);
    //shift right
    af.a = af.a >> 1u;
    //set bit 7 to carry flag
    af.a |= ((af.f & FLAG_C) << 3u);

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit0 == 0x01);

    return 1;
}

// ROW x2

//if z flag is 0,jump (immediate s8) steps from the current address. otherwise, go to the end of the instruction
uint8_t Gameboy::OP_0x20() {
    if (!readFlag('Z')) {
        auto jumpSteps = static_cast<int8_t>(read(++pc));
        pc += jumpSteps;
        //decrement since we will increment right after the instruction
        pc--;
        return 3;
    }
    pc++;
    return 2;
}


//Load the 2 bytes of immediate data into register pair HL.
uint8_t Gameboy::OP_0x21() {
    uint8_t low = read(++pc);
    uint8_t high = read(++pc);
    hl.h = high;
    hl.l = low;
    return 3;
}

//Store the contents of register A into the memory location specified by register pair HL, and simultaneously increment the contents of HL.
uint8_t Gameboy::OP_0x22() {
    write(hl.reg16, af.a);
    hl.reg16++;
    return 2;
}

//Increment the contents of register pair HL by 1.
uint8_t Gameboy::OP_0x23() {
    hl.reg16++;
    return 2;
}

//Increment the contents of register H by 1.
uint8_t Gameboy::OP_0x24(){
    uint8_t oldh = hl.h;
    hl.h++;
    setFlag('Z', hl.h==0);
    setFlag('N', false);
    setFlag('H', ((oldh & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register H by 1.
uint8_t Gameboy::OP_0x25() {
    uint8_t oldh = hl.h;
    hl.h--;
    setFlag('Z', hl.h==0);
    setFlag('N', true);
    setFlag('H', (oldh & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register H.
uint8_t Gameboy::OP_0x26() {
    pc++;
    hl.h = read(pc);
    return 2;
}

// Adjust the accumulator (register A) to a binary-coded decimal (BCD) number after BCD addition and subtraction operations.
// turns A from hex to decimal coded binary
// Ex. 0x0F (15 in decimal) becomes 0x15 (visually 15)
uint8_t Gameboy::OP_0x27() {
    uint8_t oldA = af.a;

    if (!readFlag('N')) { // last op was addition
        if (readFlag('C') || af.a > 0x99) { 
            oldA += 0x60;
            setFlag('C', true);
        }
        if (readFlag('H') || (af.a & 0x0F) > 0x09) { 
            oldA += 0x06; 
        }
    } else { // last op was subtraction
        if (readFlag('C')) { oldA -= 0x60; }
        if (readFlag('H')) { oldA -= 0x06; }
    }

    af.a = oldA;

    setFlag('Z', oldA == 0);
    setFlag('H', false);
    return 1;
}

//If the Z flag is 1, jump s8 steps from the current address stored in the pc 
uint8_t Gameboy::OP_0x28() {
    pc++;
    auto jumpSteps = static_cast<int8_t>(read(pc));
    // if z flag is 1
    if (readFlag('Z')) {
        pc += jumpSteps;
        pc --; // adjust for automatic pc increment after opcode function
        return 3;
    }
    return 2;
}

// Add the contents of register pair HL to the contents of register pair HL, and store the results in register pair HL.
uint8_t Gameboy::OP_0x29() {
    uint16_t  oldHL = hl.reg16;
    hl.reg16 += hl.reg16;

    setFlag('N', false);
    setFlag('H', ((oldHL & 0x0FFF) + (oldHL & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHL) + static_cast<uint32_t>(oldHL)) > 0xFFFF);
    return 2;
}

// Load the contents of memory specified by register pair HL into register A, and simultaneously increment the contents of HL.
uint8_t Gameboy::OP_0x2A() {
    af.a = read(hl.reg16);
    hl.reg16++;
    return 2;
}

// Decrement the contents of register pair HL by 1.
uint8_t Gameboy::OP_0x2B() {
    hl.reg16--;
    return 2;
}

//Increment the contents of register L by 1.
uint8_t Gameboy::OP_0x2C() {
    uint8_t oldL = hl.l;
    hl.l++;
    setFlag('Z', hl.l==0);
    setFlag('N', false);
    setFlag('H', ((oldL & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register L by 1.
uint8_t Gameboy::OP_0x2D() {
    uint8_t oldL = hl.l;
    hl.l--;
    setFlag('Z', hl.l==0);
    setFlag('N', true);
    setFlag('H', (oldL & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register L.
uint8_t Gameboy::OP_0x2E() {
    pc++;
    hl.l = read(pc);
    return 2;
}

// Rotate the contents of register A to the right, through the carry (CY) flag.
// The contents of bit 7 are copied to bit 6, and the previous contents of bit 6 (before the copy) are copied to bit 5. 
// The same operation is repeated in sequence for the rest of the register. The previous contents of the carry flag are copied to bit 7.
uint8_t Gameboy::OP_0x2F() {
    //gets old 0 bit
    uint8_t oldBit7 = (af.a >> 7u) & 0x01;
    //shift left
    af.a = af.a << 1u;
    //set bit 0 to carry flag
    if (readFlag('C')) {
        af.a |= 0x01;
    }

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit7 == 0x01);

    return 1;
}


// ROW x3
//if c flag is 0,jump (immediate s8) steps from the current address. otherwise, go to the end of the instruction
uint8_t Gameboy::OP_0x30() {
    if (!readFlag('C')) {
        auto jumpSteps = static_cast<int8_t>(read(++pc));
        pc += jumpSteps;
        //decrement since we will increment right after the instruction
        pc--;
        return 3;
    }
    pc++;
    return 2;
}

//load the two bytes of immediate data into SP
uint8_t Gameboy::OP_0x31() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    sp = (highByte << 8u) | lowByte;
    return 3;
}

//write the contents of register A into the location specified by hl
uint8_t Gameboy::OP_0x32() {
    write(hl.reg16, af.a);
    return 2;
}

//increment sp by 1
uint8_t Gameboy::OP_0x33() {
    sp++;
    return 2;
}

//increment HL by 1
uint8_t Gameboy::OP_0x34() {
    uint8_t oldHl = read(hl.reg16);
    write(hl.reg16, oldHl+1);
    uint8_t newHl = oldHl+1;
    setFlag('Z', newHl == 0);
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 3;
}

//decrement HL by 1
uint8_t Gameboy::OP_0x35() {
    uint8_t oldHl = read(hl.reg16);
    write(hl.reg16, oldHl-1);
    uint8_t newHl = oldHl-1;
    setFlag('Z', newHl == 0);
    setFlag('N', true);
    setFlag('H', (oldHl & 0x0F) == 0x00);
    return 3;
}

//load the immediate 8 bytes into hl
uint8_t Gameboy::OP_0x36() {
    uint8_t nextByte = read(++pc);
    write(hl.reg16, nextByte);
    return 3;
}

//set the carry flag to 1
uint8_t Gameboy::OP_0x37() {
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', true);
    return 1;
}

// If the C flag is 1, jump s8 steps from the current address stored in the pc
uint8_t Gameboy::OP_0x38() {
    pc++;
    int8_t jumpSteps = static_cast<int8_t>(read(pc));
    // if z flag is 0
    if (readFlag('C')) {
        pc += jumpSteps;
        pc --; // adjust for automatic pc increment after opcode function
        return 3;
    }
    // otherwise do nothing
    return 2;
}

// Add the contents of SP to the contents of register pair HL, and store the results in register pair HL.
uint8_t Gameboy::OP_0x39() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 += sp;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (sp & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHl) + static_cast<uint32_t>(sp)) > 0xFFFF);
    return 2;
}

//read the contents of memory at the address stored in hl, and store it in a. then, decrement hl
uint8_t Gameboy::OP_0x3A() {
    af.a = read(hl.reg16);
    hl.reg16--;
    return 2;
}

//decrement sp by 1
uint8_t Gameboy::OP_0x3B() {
    sp--;
    return 2;
} 

//increment contents of register a by 1
uint8_t Gameboy::OP_0x3C() {
    uint8_t old = af.a;
    af.a++;
    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//decrement the contents of register a by 1
uint8_t Gameboy::OP_0x3D() {
    uint8_t old = af.a;
    af.a--;
    setFlag('Z', af.a==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//read immediate into a
uint8_t Gameboy::OP_0x3E() {
    af.a = read(++pc);
    return 2;
}

//flip the carry flag
uint8_t Gameboy::OP_0x3F() {
    setFlag('C', !readFlag('C'));
    return 1;
}

// ROW x4

//Load the contents of register B into register B.
uint8_t Gameboy::OP_0x40() {
    bc.b = bc.b;
    return 1;
}

// Load the contents of register C into register B
uint8_t Gameboy::OP_0x41() {
    bc.b = bc.c;
    return 1;
}

// Load the contents of register D into register B.
uint8_t Gameboy::OP_0x42() {
    bc.b = de.d;
    return 1;
}

// Load the contents of register E into register B.
uint8_t Gameboy::OP_0x43() {
    bc.b = de.e;
    return 1;
}

// Load the contents of register H into register B.
uint8_t Gameboy::OP_0x44() {
    bc.b = hl.h;
    return 1;
}

// Load the contents of register L into register B.
uint8_t Gameboy::OP_0x45() {
    bc.b = hl.l;
    return 1;    
}

//Load the 8-bit contents of memory specified by register pair HL into register B.
uint8_t Gameboy::OP_0x46() {
    bc.b = read(hl.reg16);
    return 2;
}

//Load the contents of register A into register B.
uint8_t Gameboy::OP_0x47() {
    bc.b = af.a;
    return 1;
}

//Load the contents of register B into register C.
uint8_t Gameboy::OP_0x48() {
    bc.c = bc.b;
}

//Load the contents of register C into register C.
uint8_t Gameboy::OP_0x49() {
    bc.c = bc.c;
    return 1;
}

// Load the contents of register D into register C.
uint8_t Gameboy::OP_0x4A() {
    bc.c = de.d;
    return 1;
}

//Load the contents of register E into register C
uint8_t Gameboy::OP_0x4B() {
    bc.c = de.e;
    return 1;
}

// Load the contents of register H into register C.
uint8_t Gameboy::OP_0x4C() {
    bc.c = hl.h;
    return 1;
}

//Load the contents of register L into register C.
uint8_t Gameboy::OP_0x4D() {
    bc.c = hl.h;
    return 1;
}

// Load the 8-bit contents of memory specified by register pair HL into register C.
uint8_t Gameboy::OP_0x4E() {
    bc.c = read(hl.reg16);
    return 2;
}

//Load the contents of register A into register C.
uint8_t Gameboy::OP_0x4F() {
    bc.c = af.a;
    return 1;
}


// ROW x5
//row 5 is super simple, just load into D (from 0-7) then load into E (from 8-F)
uint8_t Gameboy::OP_0x50() {
    de.d = bc.b;
    return 1;
}

uint8_t Gameboy::OP_0x51() {
    de.d = bc.c;
    return 1;
}

uint8_t Gameboy::OP_0x52() {
    de.d = de.d;
    return 1;
}

uint8_t Gameboy::OP_0x53() {
    de.d = de.e;
    return 1;
}

uint8_t Gameboy::OP_0x54() {
    de.d = hl.h;
    return 1;
}

uint8_t Gameboy::OP_0x55() {
    de.d = hl.l;
    return 1;
}

uint8_t Gameboy::OP_0x56() {
    de.d = read(hl.reg16);
    return 2;
}

uint8_t Gameboy::OP_0x57() {
    de.d = af.a;
    return 1;
}

uint8_t Gameboy::OP_0x58() {
    de.e = bc.b;
    return 1;
}

uint8_t Gameboy::OP_0x59() {
    de.e = bc.c;
    return 1;
}

uint8_t Gameboy::OP_0x5A() {
    de.e = de.d;
    return 1;
}

uint8_t Gameboy::OP_0x5B() {
    de.e = de.e;
    return 1;
}

uint8_t Gameboy::OP_0x5C() {
    de.e = hl.h;
    return 1;
}

uint8_t Gameboy::OP_0x5D() {
    de.e = hl.l;
    return 1;
}

uint8_t Gameboy::OP_0x5E() {
    de.e = read(hl.reg16);
    return 2;
}

uint8_t Gameboy::OP_0x5F() {
    de.e = af.a;
    return 1;
}


// ROW x6
//row 6 is also super simple loading into H and then into L
uint8_t Gameboy::OP_0x60() {
    hl.h = bc.b;
    return 1;
}

uint8_t Gameboy::OP_0x61() {
    hl.h = bc.c;
    return 1;
}

uint8_t Gameboy::OP_0x62() {
    hl.h = de.d;
    return 1;
}

uint8_t Gameboy::OP_0x63() {
    hl.h = de.e;
    return 1;
}

uint8_t Gameboy::OP_0x64() {
    hl.h = hl.h;
    return 1;
}

uint8_t Gameboy::OP_0x65() {
    hl.h = hl.l;
    return 1;
}

uint8_t Gameboy::OP_0x66() {
    hl.h = read(hl.reg16);
    return 2;
}

uint8_t Gameboy::OP_0x67() {
    hl.h = af.a;
    return 1;
}

uint8_t Gameboy::OP_0x68() {
    hl.h = bc.b;
    return 1;
}

uint8_t Gameboy::OP_0x69() {
    hl.l = bc.c;
    return 1;
}

uint8_t Gameboy::OP_0x6A() {
    hl.l = de.d;
    return 1;
}

uint8_t Gameboy::OP_0x6B() {
    hl.l = de.e;
    return 1;
}

uint8_t Gameboy::OP_0x6C() {
    hl.l = hl.h;
    return 1;
}

uint8_t Gameboy::OP_0x6D() {
    hl.l = hl.l;
    return 1;
}

uint8_t Gameboy::OP_0x6E() {
    hl.l = read(hl.reg16);
    return 2;
}

uint8_t Gameboy::OP_0x6F() {
    hl.l = af.a;
    return 1;
}



// ROW 7

//Store the contents of register B in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x70() {
    write(hl.reg16, bc.b);
    return 2;
}

//Store the contents of register C in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x71() {
    write(hl.reg16, bc.c);
    return 2;
}

//Store the contents of register D in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x72() {
    write(hl.reg16, de.d);
    return 2;
}

// Store the contents of register E in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x73() {
    write(hl.reg16, de.e);
    return 2;
}
// Store the contents of register H in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x74() {
    write(hl.reg16, hl.h);
    return 2;
}

// Store the contents of register L in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x75() {
    write(hl.reg16, hl.l);
    return 2;
}

// HALT INSTRUCTION
// pauses the CPU in a low-power state to save battery while keeping peripheral systems like the LCD and RAM active.
// The CPU remains frozen at the current Program Counter until it is "woken up" by a hardware interrupt or a system reset. 
// Once an interrupt occurs, the CPU resumes execution, either by jumping to an interrupt handler or simply continuing to the next instruction.
uint8_t Gameboy::OP_0x76() {
    halted = true;
    return 1;
}

// Store the contents of register A in the memory location specified by register pair HL.
uint8_t Gameboy::OP_0x77() {
    write(hl.reg16, af.a);
    return 2;
}

// Load the contents of register B into register A.
uint8_t Gameboy::OP_0x78() {
    af.a = bc.b;
    return 1;
}

//Load the contents of register C into register A
uint8_t Gameboy::OP_0x79() {
    af.a = bc.c;
    return 1;
}


// Load the contents of register D into register A.
uint8_t Gameboy::OP_0x7A() {
    af.a = de.d;
    return 1;
}

uint8_t Gameboy::OP_0x7B() {
    af.a = de.e;
    return 1;
}

// Load the contents of register H into register A.
uint8_t Gameboy::OP_0x7C() {
    af.a = hl.h;
    return 1;
}

uint8_t Gameboy::OP_0x7D() {
    af.a = hl.l;
    return 1;
}

// Load the 8-bit contents of memory specified by register pair HL into register A.
uint8_t Gameboy::OP_0x7E() {
    af.a = read(hl.reg16);
    return 2;
}

// Load the contents of register A into register A.
uint8_t Gameboy::OP_0x7F() {
    af.a = af.a;
    return 1;
}

// ROW x8
// Add the contents of register B to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x80() {
    uint8_t oldA = af.a;
    af.a = af.a + bc.b;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.b & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.b)) > 0xFF);

    return 1;
}

// Add the contents of register C to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x81() {
    uint8_t oldA = af.a;
    af.a = af.a + bc.c;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.c & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.c)) > 0xFF);

    return 1;
}

//Add the contents of register D to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x82() {
    uint8_t oldA = af.a;
    af.a = af.a + de.d;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.d & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.d)) > 0xFF);

    return 1;
}

// Add the contents of register E to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x83() {
    uint8_t oldA = af.a;
    af.a = af.a + de.e;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.e & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.e)) > 0xFF);

    return 1;
}

// Add the contents of register H to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x84() {
    uint8_t oldA = af.a;
    af.a = af.a + hl.h;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.h & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.h)) > 0xFF);

    return 1;
}

// Add the contents of register L to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x85() {
    uint8_t oldA = af.a;
    af.a = af.a + hl.l;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.l & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.l)) > 0xFF);

    return 1;
}

// Add the contents of memory specified by register pair HL to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x86() {
    uint8_t val = read(hl.reg16);
    uint8_t oldA = af.a;
    af.a = af.a + val;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(val)) > 0xFF);

    return 2;
}

// Add the contents of register A to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x87() {
    uint8_t oldA = af.a;
    uint8_t val = af.a;
    af.a = af.a + val;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(val)) > 0xFF);

    return 1;
}

// Add the contents of register B and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x88() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.b) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.b & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register C and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x89() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.c) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.c & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register D and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x8A() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.d) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.d & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register E and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x8B() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.e) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.e & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register H and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x8C() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.h) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.h & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register L and the CY flag to the contents of register A, and store the results in register A
uint8_t Gameboy::OP_0x8D() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.l) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.l & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of memory specified by register pair HL and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x8E() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t val = static_cast<uint16_t>(read(hl.reg16));
    uint16_t result = static_cast<uint16_t>(oldA) + val + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 2;
}

// Add the contents of register A and the CY flag to the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0x8F() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(oldA) + cy;
    
    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (oldA & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}


// ROW x9
//subtract b from a
uint8_t Gameboy::OP_0x90() {
    return OpcodeHelpers::SUB(af.a, bc.b, *this);
}

//subtract c from a
uint8_t Gameboy::OP_0x91() {
    return OpcodeHelpers::SUB(af.a, bc.c, *this);
}

//subtract d from a
uint8_t Gameboy::OP_0x92() {
    return OpcodeHelpers::SUB(af.a, de.d, *this);
}

//subtract e from a
uint8_t Gameboy::OP_0x93() {
    return OpcodeHelpers::SUB(af.a, de.e, *this);
}

//subtract h from a
uint8_t Gameboy::OP_0x94() {
    return OpcodeHelpers::SUB(af.a, hl.h, *this);
}

//subtract l from a
uint8_t Gameboy::OP_0x95() {
    return OpcodeHelpers::SUB(af.a, hl.l, *this);
}

//subtract the contents of memory at HL from a
uint8_t Gameboy::OP_0x96() {
    return OpcodeHelpers::SUB(af.a, read(hl.reg16), *this);
}

//subtract a from a, trivial but kept same logic
uint8_t Gameboy::OP_0x97() {
    return OpcodeHelpers::SUB(af.a, af.a, *this);
}

//subtract b register and carry flag from a
uint8_t Gameboy::OP_0x98() {
    return OpcodeHelpers::SBC(af.a, bc.b, *this);
}

//subtract c register and carry flag from a
uint8_t Gameboy::OP_0x99() {
    return OpcodeHelpers::SBC(af.a, bc.c, *this);
}

//subtract d register and carry flag from a
uint8_t Gameboy::OP_0x9A() {
    return OpcodeHelpers::SBC(af.a, de.d, *this);
}

//subtract e register and carry flag from a
uint8_t Gameboy::OP_0x9B() {
    return OpcodeHelpers::SBC(af.a, de.e, *this);
}

//subtract h register and carry flag from a
uint8_t Gameboy::OP_0x9C() {
    return OpcodeHelpers::SBC(af.a, hl.h, *this);
}

//subtract l register and carry flag from a
uint8_t Gameboy::OP_0x9D() {
    return OpcodeHelpers::SBC(af.a, hl.l, *this);
}

//subtract e register and carry flag from a
uint8_t Gameboy::OP_0x9E() {
    return OpcodeHelpers::SBC(af.a, read(hl.reg16), *this);
}

//subtract e register and carry flag from a
uint8_t Gameboy::OP_0x9F() {
    return OpcodeHelpers::SBC(af.a, af.a, *this);
}

// ROW xA

// Take the logical AND for each bit of the contents of register B and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA0() {
    uint8_t result = af.a & bc.b;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register C and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA1() {
    uint8_t result = af.a & bc.c;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}


// Take the logical AND for each bit of the contents of register D and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA2() {
    uint8_t result = af.a & de.d;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register E and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA3() {
    uint8_t result = af.a & de.e;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register H and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA4() {
    uint8_t result = af.a & hl.h;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register L and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA5() {
    uint8_t result = af.a & hl.l;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of memory specified by register pair HL and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA6() {
    uint8_t result = af.a & read(hl.reg16);
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 2;
}

// Take the logical AND for each bit of the contents of register A and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA7() {
    uint8_t result = af.a & af.a;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register B and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA8() {
    af.a = af.a ^ bc.b;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register C and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xA9() {
    af.a = af.a ^ bc.c;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register D and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAA() {
    af.a = af.a ^ de.d;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register E and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAB() {
    af.a = af.a ^ de.e;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register H and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAC() {
    af.a = af.a ^ hl.h;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register L and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAD() {
    af.a = af.a ^ hl.l;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of memory specified by register pair HL and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAE() {
    af.a = af.a ^ read(hl.reg16);

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 2;
}

// Take the logical exclusive-OR for each bit of the contents of register A and the contents of register A, and store the results in register A.
uint8_t Gameboy::OP_0xAF() {
    af.a = af.a ^ af.a;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

//ROW xB
//logical or of a and b, stored in a
uint8_t Gameboy::OP_0xB0() {
    return OpcodeHelpers::OR(af.a, bc.b, *this);
}

//logical or of a and c, stored in a
uint8_t Gameboy::OP_0xB1() {
    return OpcodeHelpers::OR(af.a, bc.c, *this);
}

//logical or of a and d, stored in a
uint8_t Gameboy::OP_0xB2() {
    return OpcodeHelpers::OR(af.a, de.d, *this);
}

//logical or of a and e, stored in a
uint8_t Gameboy::OP_0xB3() {
    return OpcodeHelpers::OR(af.a, de.e, *this);
}

//logical or of a and h, stored in a
uint8_t Gameboy::OP_0xB4() {
    return OpcodeHelpers::OR(af.a, hl.h, *this);
}

//logical or of a and l, stored in a
uint8_t Gameboy::OP_0xB5() {
    return OpcodeHelpers::OR(af.a, hl.l, *this);
}

//logical or of a and contents of memory at address in hl, stored in a
uint8_t Gameboy::OP_0xB6() {
    return OpcodeHelpers::OR(af.a, read(hl.reg16), *this);
}

//logical or of a and a, stored in a
uint8_t Gameboy::OP_0xB7() {
    return OpcodeHelpers::OR(af.a, af.a, *this);
}

//calculate a-b and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xB8() {
    return OpcodeHelpers::OR(af.a, bc.b, *this);
}

//calculate a-c and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xB9() {
    return OpcodeHelpers::OR(af.a, bc.c, *this);
}

//calculate a-d and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBA() {
    return OpcodeHelpers::OR(af.a, de.d, *this);
}

//calculate a-e and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBB() {
    return OpcodeHelpers::OR(af.a, de.e, *this);
}

//calculate a-h and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBC() {
    return OpcodeHelpers::OR(af.a, hl.h, *this);
}

//calculate a-h and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBD() {
    return OpcodeHelpers::OR(af.a, hl.l, *this);
}

//calculate a- memory at hl and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBE() {
    return OpcodeHelpers::OR(af.a, read(hl.reg16), *this);
}

//calculate a-a and set flags accordingly. same as SUB except we do not change the value of a
uint8_t Gameboy::OP_0xBF() {
    return OpcodeHelpers::OR(af.a, af.a, *this);
}

//ROW xC
//if zero flag is zero (meaning last op not 0) loads the contents of memory at the address in sp into
//the lower byte of pc, then increments and does the same for the higher byte
uint8_t Gameboy::OP_0xC0() {
    if (!readFlag('Z')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        return 5;
    }
    return 2;
}

//pop the contents of memory at sp into bc
uint8_t Gameboy::OP_0xC1() {
    bc.c = read(sp++);
    bc.b = read(sp++);
    return 3;
}

//jump to immediate 16 bit address if NZ, otherwise increment to next instruction
uint8_t Gameboy::OP_0xC2() {
    if (!readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//jump to immediate
uint8_t Gameboy::OP_0xC3() {
    uint16_t newAddress = read(++pc);
    newAddress |= (read(++pc) << 8u);
    pc = newAddress;
    pc--;
    return 4;
}

//call to immediate and push the next address to stack if NZ
uint8_t Gameboy::OP_0xC4() {
    if (!readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>(returnAddress & 0xFF00) >> 8u);
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//push bc onto the stack
uint8_t Gameboy::OP_0xC5() {
    //high byte first
    write(--sp, bc.b);
    write(--sp, bc.c);
    return 4;
}

//add the immediate 8 bit operand to the register A
uint8_t Gameboy::OP_0xC6() {
    uint8_t oldA = af.a;
    uint8_t bitToAdd = read(++pc);
    af.a = af.a + bitToAdd;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bitToAdd & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bitToAdd)) > 0xFF);

    return 2;
}

//push pc onto stack, load the 0th byte of page 0 memory into the pc, RST 0
uint8_t Gameboy::OP_0xC7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0000;
    pc--;
    return 4;
}

//return if zero, same as c0 but with the Z flag being 1
uint8_t Gameboy::OP_0xC8() {
    if (readFlag('Z')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        return 5;
    }
    return 2;
}

//return, same as c0 but we don't care about the z flag
uint8_t Gameboy::OP_0xC9() {
    uint8_t lowerByte = read(sp++);
    pc = lowerByte;
    uint8_t higherByte = read(sp++);
    pc |= (higherByte << 8u);
    return 4;
}

//jump to immediate 16 bit address if Z, otherwise increment to next instruction
uint8_t Gameboy::OP_0xCA() {
    if (readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if zero flag
uint8_t Gameboy::OP_0xCC() {
    if (readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>(returnAddress & 0xFF00) >> 8u);
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack
uint8_t Gameboy::OP_0xCD() {
    uint16_t newAddress = read(++pc);
    newAddress |= (read(++pc) << 8u);

    uint16_t returnAddress = ++pc;

    //write to memory the return address which is just the program counter incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(returnAddress & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

    pc = newAddress;
    pc--;
    return 6;
}

//add contents of immediate and CY flag to register A, store in register A
uint8_t Gameboy::OP_0xCE() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint8_t bitToAdd = read(++pc);
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bitToAdd) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bitToAdd & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 2;
}

//push pc onto stack, load the 2nd (0x08) byte of page 0 memory into the pc, RST 1
uint8_t Gameboy::OP_0xCF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0008;
    pc--;
    return 4;
}



//ROW xD
//if carry flag is zero, loads the contents of memory at the address in sp into
//the lower byte of pc, then increments and does the same for the higher byte
uint8_t Gameboy::OP_0xD0() {
    if (!readFlag('C')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        return 5;
    }
    return 2;
}

//pop the contents of memory at sp into de
uint8_t Gameboy::OP_0xD1() {
    de.e = read(sp++);
    de.d = read(sp++);
    return 3;
}

//jump to immediate 16 bit address if NC, otherwise increment to next instruction
uint8_t Gameboy::OP_0xD2() {
    if (!readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if NZ
uint8_t Gameboy::OP_0xD4() {
    if (!readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>(returnAddress & 0xFF00) >> 8u);
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//push de onto the stack
uint8_t Gameboy::OP_0xD5() {
    //high byte first
    write(--sp, de.d);
    write(--sp, de.e);
    return 4;
}

//sub the immediate 8 bit operand to the register A
uint8_t Gameboy::OP_0xD6() {
    //we return +1 since the original function returns 1, but this is 2 cycles since we read a byte
    return OpcodeHelpers::SUB(af.a, read(++pc), *this) + 1;
}

//push pc onto stack, load the 3rd byte of page 0 memory into the pc, RST 2
uint8_t Gameboy::OP_0xD7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0010;
    pc--;
    return 4;
}

//return if zero, same as D0 but with the C flag being 1
uint8_t Gameboy::OP_0xD8() {
    if (readFlag('C')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        return 5;
    }
    return 2;
}

//returns after an interrupt. load the stack pointer into program counter, set IME to 1
uint8_t Gameboy::OP_0xD9() {
    IME = true;

    uint8_t lowerByte = read(sp++);
    pc = lowerByte;
    uint8_t higherByte = read(sp++);
    pc |= (higherByte << 8u);
    return 4;
}

//jump to immediate 16 bit address if C, otherwise increment to next instruction
uint8_t Gameboy::OP_0xDA() {
    if (readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if zero flag
uint8_t Gameboy::OP_0xDC() {
    if (readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>(returnAddress & 0xFF00) >> 8u);
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//sub contents of immediate and CY flag to register A, store in register A
uint8_t Gameboy::OP_0xDE() {
    //we return +1 since the original function returns 1, but this is 2 cycles since we read a byte
    return OpcodeHelpers::SBC(af.a, read(++pc), *this) + 1;
}

//push pc onto stack, load the 3rd byte of page 0 memory into the pc, RST 3
uint8_t Gameboy::OP_0xDF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0018;
    pc--;
    return 4;
}

//ROW xE
//loads the contents of register A into the mem at the address specified by the immediate, where the immediate
//specifies the least significant byte of the memory, and FF is always the most significant byte
uint8_t Gameboy::OP_0xE0() {
    uint16_t newAddress = 0xFF00;
    newAddress |= read(++pc);

    write(newAddress, af.a);
    return 3;
}

//pop the contents of memory at sp into hl
uint8_t Gameboy::OP_0xE1() {
    hl.l = read(sp++);
    hl.h = read(sp++);
    return 3;
}

//load the contents of A into memory at address specified by 0xFF(contents of C).
uint8_t Gameboy::OP_0xE2() {
    uint16_t newAddress = 0xFF00;
    newAddress |= bc.c;

    write(newAddress, af.a);
    return 3;
}

//push hl onto the stack
uint8_t Gameboy::OP_0xE5() {
    //high byte first
    write(--sp, hl.h);
    write(--sp, hl.l);
    return 4;
}

//bitwise AND on register A and the 8 bit immediate, stored in register A
uint8_t Gameboy::OP_0xE6() {
    uint8_t result = af.a & read(++pc);
    af.a = result;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 2;
}

//RST 4
uint8_t Gameboy::OP_0xE7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0020;
    pc--;
    return 4;
}

//add the contents of the signed 8 bit immediate to the stack pointer
//half carry determined by bit 3 -> 4,
//carry determined by bit 7 -> 8
uint8_t Gameboy::OP_0xE8() {
    uint16_t oldSP = sp;
    auto immediate = static_cast<int8_t>(read(++pc));
    sp = oldSP + immediate;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', ((oldSP & 0x000F) + (immediate & 0x000F)) > 0x000F);
    setFlag('C', ((oldSP & 0x00FF) + (immediate & 0x00FF)) > 0x00FF);

    return 4;
}

//load HL into stack pointer
uint8_t Gameboy::OP_0xE9() {
    pc = hl.reg16;
    return 1;
}

//store the contents of register A in memory at the address stored in the immediate
uint8_t Gameboy::OP_0xEA() {
    uint16_t address = read(++pc);
    address |= (read(++pc) << 8u);

    write(address, af.a);
    return 4;
}

//xor with the 8 bit immediate
uint8_t Gameboy::OP_0xEE() {
    uint8_t immediate = read(++pc);
    af.a = af.a ^ immediate;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 2;
}

//RST 5
uint8_t Gameboy::OP_0xEF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0028;
    pc--;
    return 4;
}

//ROW xF
//loads the contents of mem at the address specified by the immediate into register A, the immediate
//specifies the least significant byte of the memory, and FF is always the most significant byte
uint8_t Gameboy::OP_0xF0() {
    uint16_t newAddress = 0xFF00;
    newAddress |= read(++pc);

    af.a = read(newAddress);
    return 3;
}

//pop the contents of memory at sp into af
uint8_t Gameboy::OP_0xF1() {
    af.f = read(sp++);
    af.a = read(sp++);
    return 3;
}

//load memory at address in register C (0xFF(c value)) where c stores last 8 bits into register a
uint8_t Gameboy::OP_0xF2() {
    uint16_t newAddress = 0xFF00;
    newAddress |= read(bc.c);

    af.a = read(newAddress);
    return 3;
}

//disables interrupts
uint8_t Gameboy::OP_0xF3() {
    IME = false;
    return 1;
}

//push AF onto the stack
uint8_t Gameboy::OP_0xF5() {
    //high byte first
    write(--sp, af.a);
    write(--sp, af.f);
    return 4;
}

//logical OR with the immediate operand and A, stored in A
uint8_t Gameboy::OP_0xF6() {
    return OpcodeHelpers::OR(af.a, read(++pc), *this) + 1;
}

//RST 6
uint8_t Gameboy::OP_0xF7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0030;
    pc--;
    return 4;
}

//add the signed immediate to the stack pointer, store in HL
uint8_t Gameboy::OP_0xF8() {
    uint16_t oldSP = sp;
    auto immediate = static_cast<int8_t>(read(++pc));
    hl.reg16 = oldSP + immediate;


    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', ((oldSP & 0x000F) + (immediate & 0x000F)) > 0x000F);
    setFlag('C', ((oldSP & 0x00FF) + (immediate & 0x00FF)) > 0x00FF);

    return 3;
}

//load HL into SP
uint8_t Gameboy::OP_0xF9() {
    sp = hl.reg16;
    return 2;
}

//load ram at address in 16 bit immediate into register A
uint8_t Gameboy::OP_0xFA() {
    uint16_t address = read(++pc);
    address |= (read(++pc) << 8u);

    af.a = read(address);
    return 4;
}

//enable interrupts
uint8_t Gameboy::OP_0xFB() {
    IME = true;
    return 1;
}

//compare register A with immediate. doesn't affect register A
uint8_t Gameboy::OP_0xFE() {
    return OpcodeHelpers::CP(af.a, read(++pc), *this) + 1;
}

//RST 6
uint8_t Gameboy::OP_0xFF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>(pc & 0xFF00) >> 8u);
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0038;
    pc--;
    return 4;
}



