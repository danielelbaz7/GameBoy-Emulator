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

uint8_t OpcodeHelpers::CP(uint8_t a, uint8_t toSubtract, Gameboy& gb) {
    uint8_t computedValue = a - toSubtract;
    gb.setFlag('Z', computedValue == 0);
    gb.setFlag('N', true);
    gb.setFlag('H', (a & 0xF) < (toSubtract & 0x0F));
    gb.setFlag('C', a < toSubtract);
    return 1;
}

uint8_t OpcodeHelpers::RES(uint8_t &reg, uint8_t bit) {
    reg &= ~(0x01 << bit);
    return 2;
}

uint8_t OpcodeHelpers::SET(uint8_t &reg, uint8_t bit) {
    reg &= (0x01 << bit);
    return 2;
}

uint8_t OpcodeHelpers::RES(uint8_t address, uint8_t bit) {
    uint8_t reg = read(address);
    reg &= ~(0x01 << bit);
    write(address, reg);
    return 4;
}

uint8_t OpcodeHelpers::SET(uint8_t address, uint8_t bit) {
    uint8_t reg = read(address);
    reg &= (0x01 << bit);
    write(address, reg);
    return 4;
}

uint8_t OpcodeHelpers::BIT(uint16_t address, uint8_t bit, Gameboy &gb) {
    uint8_t mask = (1u << bit);
    uint8_t value = gb.read(address);

    // 0110 (val)
    // 0100 (bit/mask)
    // 0100 (result -> not zero so Z is false)

    // set Z flag to true is mask & value are zero (bit in value is zero)
    gb.setFlag('Z', (mask & value) == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', true);

    return 3;
}

uint8_t OpcodeHelpers::BIT(uint8_t &reg, uint8_t bit, Gameboy& gb) {
    uint8_t mask = (1u << bit);
    
    gb.setFlag('Z', (mask & reg) == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', true);

    return 2;
}

uint8_t OpcodeHelpers::RLC(uint8_t &reg, Gameboy& gb) {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (reg & 0x80) >> 7u;
    //shift left
    reg = reg << 1u;
    //set bit 0 to old bit 7
    reg |= oldBit7;

    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit7 == 0x01);
    return 2;
}

uint8_t OpcodeHelpers::RRC(uint8_t &reg, Gameboy& gb) {
    uint8_t oldBit0 = (reg & 0x01) << 7u;
    reg = reg >> 1u;
    reg |= oldBit0;

    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit0 == 0x80);

    return 2;
}

uint8_t OpcodeHelpers::RL(uint8_t &reg, Gameboy& gb) {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (reg & 0x80) >> 7u;
    //shift left
    reg = reg << 1u;
    //set bit 0 to carry flag
    reg |= ((reg & gb.FLAG_C) >> 4u);

    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit7 == 0x01);

    return 2;
}