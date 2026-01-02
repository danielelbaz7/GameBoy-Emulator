//
// Created by Daniel Elbaz on 12/29/25.
//

#ifndef GAMEBOYEMULATOR_OPCODEHELPERS_H
#define GAMEBOYEMULATOR_OPCODEHELPERS_H
#include <cstdint>

#include "Gameboy.h"


namespace OpcodeHelpers {
    uint8_t SUB(uint8_t &a, uint8_t toSubtract, Gameboy& gb);
    uint8_t SBC(uint8_t &a, uint8_t toSubtract, Gameboy& gb);

    uint8_t OR(uint8_t &a, uint8_t toOrWith, Gameboy& gb);
    uint8_t CP(uint8_t a, uint8_t toOrWith, Gameboy& gb);

    uint8_t RES(uint8_t &reg, uint8_t bit);
    uint8_t SET(uint8_t &reg, uint8_t bit);
    
    uint8_t RES(uint16_t address, uint8_t bit, Gameboy& gb);
    uint8_t SET(uint16_t address, uint8_t bit, Gameboy& gb);

    uint8_t RLC(uint8_t &reg, Gameboy& gb);
    uint8_t RRC(uint8_t &reg, Gameboy& gb);
    uint8_t RL(uint8_t &reg, Gameboy& gb);
    uint8_t RR(uint8_t &reg, Gameboy& gb);
    uint8_t SLA(uint8_t &reg, Gameboy& gb);
    uint8_t SRA(uint8_t &reg, Gameboy& gb);
    uint8_t SWAP(uint8_t &reg, Gameboy& gb);
    uint8_t SRL(uint8_t &reg, Gameboy& gb);

    uint8_t BIT(uint16_t address, uint8_t bit, Gameboy& gb);
    uint8_t BIT(uint8_t &reg, uint8_t bit, Gameboy& gb);

};

#endif //GAMEBOYEMULATOR_OPCODEHELPERS_H