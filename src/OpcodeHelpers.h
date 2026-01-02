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

};


#endif //GAMEBOYEMULATOR_OPCODEHELPERS_H