//
// Created by Daniel Elbaz on 1/4/26.
//

#include "Memory.h"

#include <fstream>
#include <iostream>
#include <array>
#include <cstdint>
#include "PPU.h"


std::array<uint8_t, 16> Memory::ReadTile(uint8_t tileID, MemoryAccessor caller) {
    std::array<uint8_t, 16> tileData{};
    uint16_t addressToRead = 0x8000 + (tileID * 16);

    //if lcdc4 is 1, then we look starting in block 0. else, tile id becomes its signed version so we
    if (((Read(0xFF40) & 0x10)) == 0) {
        //start at the beginning of block 2, the tileID might be negative and this will go to block 1 for us
        addressToRead = 0x9000 + static_cast<int8_t>(tileID) * 16;
    }

    for(uint8_t curByte = 0; curByte < 16; curByte++) {
        tileData[curByte] = Read(addressToRead + curByte);
    }

    return tileData;
}



//write to the scanline register to indicate which scanline we are on
void Memory::WriteScanline(uint8_t value) {
    io[68] = value;
}

uint8_t Memory::Read(uint16_t address, MemoryAccessor caller) {
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
        //disable during draw phase for cpu
        return (ppu->currentMode==PPUMode::Draw  && caller != MemoryAccessor::PPU) ? 0xFF : vram[address - 0x8000];
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
        return (isOAMDisabledByPPU & caller != MemoryAccessor::PPU) ? 0xFF : oam[address - 0xFE00];
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

void Memory::Write(uint16_t address, uint8_t byteToWrite) {
    //handles eram disable/enable
    if (address == 0xFF02 && ((byteToWrite == 0x81))) {
        std::cout << Read(0xFF01) << std::flush;
    }
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

//rom loading function

void Memory::LoadRom(char const* filename) {
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

#include "Memory.h"