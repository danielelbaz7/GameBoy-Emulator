//
// Created by Daniel Elbaz on 12/29/25.
//

#include "OpcodeHelpers.h"

uint8_t OpcodeHelpers::SUB(uint8_t &a, uint8_t toSubtract, CPU& gb) {
    uint8_t old = a;
    a -= toSubtract;
    gb.setFlag('Z', a == 0);
    gb.setFlag('N', true);
    gb.setFlag('H', (old & 0xF) < (toSubtract & 0x0F));
    gb.setFlag('C', old < toSubtract);
    return 1;
}

uint8_t OpcodeHelpers::SBC(uint8_t &a, uint8_t toSubtract, CPU& gb) {
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

uint8_t OpcodeHelpers::OR(uint8_t &a, uint8_t toOrWith, CPU &gb) {
    a |= toOrWith;
    gb.setFlag('Z', a == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', false);
    return 1;
}

uint8_t OpcodeHelpers::CP(uint8_t a, uint8_t toSubtract, CPU& gb) {
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
    reg |= (0x01 << bit);
    return 2;
}

uint8_t OpcodeHelpers::RES(uint16_t address, uint8_t bit, CPU& gb) {
    uint8_t byteAtAddress = gb.read(address);
    byteAtAddress &= ~(0x01 << bit);
    gb.write(address, byteAtAddress);
    return 4;
}

uint8_t OpcodeHelpers::SET(uint16_t address, uint8_t bit, CPU& gb) {
    uint8_t byteAtAddress = gb.read(address);
    byteAtAddress |= (0x01 << bit);
    gb.write(address, byteAtAddress);
    return 4;
}

uint8_t OpcodeHelpers::BIT(uint16_t address, uint8_t bit, CPU &gb) {
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

uint8_t OpcodeHelpers::BIT(uint8_t &reg, uint8_t bit, CPU& gb) {
    uint8_t mask = (1u << bit);

    gb.setFlag('Z', (mask & reg) == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', true);

    return 2;
}

uint8_t OpcodeHelpers::RLC(uint8_t &reg, CPU& gb) {
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


uint8_t OpcodeHelpers::RRC(uint8_t &reg, CPU& gb) {
    uint8_t oldBit0 = (reg & 0x01) << 7u;
    reg = reg >> 1u;
    reg |= oldBit0;

    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit0 == 0x80);

    return 2;
}

uint8_t OpcodeHelpers::RL(uint8_t &reg, CPU& gb) {
    //puts the old bit in the 0th bit spot
    uint8_t oldCY = gb.readFlag('C') ? 0x10 : 0;
    oldCY = oldCY >> 4u;
    uint8_t oldBit7 = (reg & 0x80) >> 7u;
    //shift left
    reg = reg << 1u;
    //set bit 0 to old bit 7
    reg |= oldCY;

    gb.setFlag('Z', reg==0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit7 == 0x01);

    return 2;
}

uint8_t OpcodeHelpers::RR(uint8_t &reg, CPU& gb) {
    //puts the old bit in the 0th bit spot
    uint8_t oldCY = gb.readFlag('C') ? 0x10 : 0;
    oldCY = oldCY << 3u;
    uint8_t oldBit0 = (reg & 0x01);
    //shift right
    reg = reg >>  1u;
    //set bit 0 to old bit 7
    reg |= oldCY;

    gb.setFlag('Z', reg==0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', oldBit0 == 0x01);

    return 2;
}

uint8_t OpcodeHelpers::SWAP(uint8_t &reg, CPU& gb) {
    uint8_t oldHigh = reg & 0xF0;
    uint8_t oldLow = reg & 0x0F;
    // adjust old bits
    oldHigh = oldHigh >> 4u;
    oldLow = oldLow << 4u;
    reg = oldLow | oldHigh;

    gb.setFlag('Z', reg ==0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);
    gb.setFlag('C', false);

    return 2;
}

uint8_t OpcodeHelpers::SRL(uint8_t &reg, CPU& gb) {
    uint8_t mask = 1u;
    gb.setFlag('C', (mask & reg) != 0);
    // shift right
    reg = reg >> 1u;
    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);

    return 2;
}

uint8_t OpcodeHelpers::SLA(uint8_t &reg, CPU& gb) {
    uint8_t mask = (1u << 7u);
    // 1000 0000
    gb.setFlag('C', (mask & reg) != 0);
    // shift left
    reg = reg << 1u;
    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);

    return 2;
}

uint8_t OpcodeHelpers::SRA(uint8_t &reg, CPU& gb) {
    uint8_t mask = 1u;
    uint8_t old7 = (reg & 0x80);
    gb.setFlag('C', (mask & reg) != 0);
    // shift right
    reg = reg >> 1u;
    reg = reg | old7;
    gb.setFlag('Z', reg == 0);
    gb.setFlag('N', false);
    gb.setFlag('H', false);

    return 2;
}

