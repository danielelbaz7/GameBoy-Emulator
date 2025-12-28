#include <vector>
#include <fstream>
#include <iostream>
#include "./Gameboy.h"

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

//flag setting
// added breaks and '&=' instead of just '&'
void Gameboy::setFlag(char flagName, bool flagValue) {
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

bool Gameboy::readFlag(char flagName) const {
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

//TO IMPLEMENT
uint8_t Gameboy::OP_0x10() {
    //stop command, we will not implement halting the cpu for now
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

// ROW x2
// If the Z flag is 0, jump s8 steps from the current address stored in the pc
uint8_t Gameboy::OP_0x20() {
    pc++;
    int8_t jumpSteps = static_cast<int8_t>(read(pc));
    // if z flag is 0
    if (!readFlag('Z')) {
        pc += jumpSteps;
        pc --; // adjust for automatic pc increment after opcode function
        return 3;
    }
    // otherwise do nothing
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
    
}

//Load the contents of memory specified by register pair HL into register A, and simultaneously increment the contents of HL.
uint8_t Gameboy::OP_0x2A() {

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
    setFlag('C', (static_cast<uint32_t>(oldHl) + static_cast<uint32_t>(sp.reg16)) > 0xFFFF);
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



