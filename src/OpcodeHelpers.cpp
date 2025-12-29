//
// Created by Daniel Elbaz on 12/29/25.
//

#include "OpcodeHelpers.h"

uint8_t OpcodeHelpers::SUB(uint8_t &a, uint8_t toSubtract, Gameboy& gb) {
    uint8_t old = a;
    a -= toSubtract;
    gb.setFlag('Z', a == 0);
    gb.setFlag('N', true);
    gb.setFlag('H', (old & 0xF) < (toSubtract & 0x0F));
    gb.setFlag('C', old < toSubtract);
    return 1;
}

uint8_t OpcodeHelpers::SBC(uint8_t &a, uint8_t toSubtract, Gameboy& gb) {
    uint8_t old = a;
    uint8_t flagValue = gb.readFlag('C') ? 1 : 0;

    a -= toSubtract;
    a -= flagValue;

    gb.setFlag('Z', a == 0);
    gb.setFlag('N', true);
    gb.setFlag('H', (old & 0xF) < (flagValue+(toSubtract & 0xF)));
    gb.setFlag('C', old < (flagValue+toSubtract));
    return 1;
}

uint8_t OpcodeHelpers::OR(uint8_t &a, uint8_t toOrWith, Gameboy &gb) {
    a |= toOrWith;
    gb.setFlag('Z', a == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', false);
    return 1;
}

uint8_t OpcodeHelpers::CP(uint8_t &a, uint8_t toSubtract, Gameboy& gb) {
    uint8_t computedValue = a - toSubtract;
    gb.setFlag('Z', computedValue == 0);
    gb.setFlag('N', true);
    gb.setFlag('H', (a & 0xF) < (toSubtract & 0x0F));
    gb.setFlag('C', a < toSubtract);
    return 1;
}
