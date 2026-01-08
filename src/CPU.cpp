#include <vector>
#include <fstream>
#include <iostream>
#include "CPU.h"

#include <thread>

#include "OpcodeHelpers.h"

CPU::CPU(Memory &m) : mem(m) {
    //initialize the opcode table upon gameboy object construction
    this->BuildOpcodeTables();
}

uint8_t CPU::read(uint16_t address) {
    return mem.Read(address);
}

void CPU::write(uint16_t address, uint8_t byteToWrite) {
    return mem.Write(address, byteToWrite);
}

bool CPU::checkInterrupt(uint8_t IF, uint8_t IE, int bitToCheck) {
    // mask to current bit
    uint8_t mask = 0x01u << bitToCheck;
    IF = IF & mask;
    IE = IE & mask;

    if ((IE & IF) !=0) {
        return true; // interrupt to handle for this bit
    }

    return false;
}

bool CPU::handleInterrupts() {
    uint8_t IF = read(0xFF0F);
    uint8_t IE = read(0xFFFF);
    uint8_t mask = 0x1F;
    if (((IF & mask) & (IE & mask)) == 0) {
        return false; // no interrupts to handle
    }
    halted = false;
    stopped = false;
    if (!IME) {
        return false; // interrupts disabled
    }

    IME = false;


    // handle interrupts (ONE MAX) from bit 0 to bit 7
    // push pc onto stack
    mem.Write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    mem.Write(--sp, static_cast<uint8_t>(pc & 0x00FF));
    if (checkInterrupt(IF, IE, 0)) {
        // handle vblank jump and reset bit 0
        pc = 0x0040;
        mem.Write(0xFF0F, (IF & 0xFE));
        return true;
    }
    if (checkInterrupt(IF, IE, 1)) {
        // handle LCD STAT jump and reset bit 1
        pc = 0x0048;
        mem.Write(0xFF0F, (IF & 0xFD));
        return true;
    }
    if (checkInterrupt(IF, IE, 2)) {
        // handle timer jump and reset bit 2
        pc = 0x0050;
        mem.Write(0xFF0F, (IF & 0xFB));
        return true;
    }
    if (checkInterrupt(IF, IE, 3)) {
        // handle serial jump and reset bit 3
        pc = 0x0058;
        mem.Write(0xFF0F, (IF & 0xF7));
        return true;
    }
    if (checkInterrupt(IF, IE, 4)) {
        if (stopped) { stopped = false; }
        // handle joypad jump and reset bit 4
        pc = 0x0060;
        mem.Write(0xFF0F, (IF & 0xEF));
        return true;
    }

    return false;
}

// Step function, executes exactly one instruction
uint8_t CPU::Step() {
    if (handleInterrupts()) {
        return 5 * dotsPerMCycle;
    }

    if (halted) {
        return 1 * dotsPerMCycle;
    }

    // get opcode
    // decode and run opcode function
    uint8_t opcode = read(pc);
    uint8_t cycleCount;
    if (opcode == 0xCB) {
        uint8_t CBOpcode = read(++pc);
        cycleCount = (this->*CBopcodeTable[CBOpcode])();
    } else {
        cycleCount = (this->*opcodeTable[opcode])();
    }
    if (imeRequest) {
        IME = true;
        imeRequest = false; // used to create a 1 instruction delay between interrupt handlings
    }
    //always increment after, we built it to expect this
    pc++;

    uint8_t TcyclesUsed = cycleCount * dotsPerMCycle;
    return cycleCount * dotsPerMCycle;
}


//flag setting
// added breaks and '&=' instead of just '&'
void CPU::setFlag(unsigned char flagName, bool flagValue) {
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

bool CPU::readFlag(unsigned char flagName) const {
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
        default: return false;
    }
}



