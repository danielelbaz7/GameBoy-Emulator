#include <vector>
#include <fstream>
#include <iostream>
#include "Gameboy.h"

#include <thread>

#include "OpcodeHelpers.h"

Gameboy::Gameboy() {
    //initialize the opcode table upon gameboy object construction
    this->BuildOpcodeTables();
}

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
    //if sc is telling it to print, print from sb
    if (address == 0xFF02 && ((byteToWrite == 0x81))) {
        std::cout << read(0xFF01) << std::flush;
    }
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


// Step function, executes exactly one instruction
uint8_t Gameboy::Step() {
    if (halted) {
        return 1;
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
    return cycleCount * 4;
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

