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

bool CPU::handleInterrupts() {
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
    // std::cout << "pc=" << std::hex << std::setw(4) << std::setfill('0') << (pc)
    //       << " val=" << std::setw(2) << (int)read(pc)
    //         << (" ")
    //         << std::setw(2) << (int)read(pc+1)
    //         << (" ")
    //         << std::setw(2) << (int)read(pc+2)
    //       << std::dec << "\n";

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
    //always increment after, we built it to expect this
    pc++;
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
        default: return false;;
    }
}



