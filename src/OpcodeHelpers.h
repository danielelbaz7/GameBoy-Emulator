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

    uint8_t RLC(uint8_t &a, Gameboy& gb); 

};


#endif //GAMEBOYEMULATOR_OPCODEHELPERS_H