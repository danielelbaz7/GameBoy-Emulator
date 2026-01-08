#include "CPU.h"
#include "OpcodeHelpers.h"

void CPU::BuildOpcodeTables() {
    //standard opcode table
    opcodeTable[0x00] = &CPU::OP_0x00;
    opcodeTable[0x01] = &CPU::OP_0x01;
    opcodeTable[0x02] = &CPU::OP_0x02;
    opcodeTable[0x03] = &CPU::OP_0x03;
    opcodeTable[0x04] = &CPU::OP_0x04;
    opcodeTable[0x05] = &CPU::OP_0x05;
    opcodeTable[0x06] = &CPU::OP_0x06;
    opcodeTable[0x07] = &CPU::OP_0x07;
    opcodeTable[0x08] = &CPU::OP_0x08;
    opcodeTable[0x09] = &CPU::OP_0x09;
    opcodeTable[0x0A] = &CPU::OP_0x0A;
    opcodeTable[0x0B] = &CPU::OP_0x0B;
    opcodeTable[0x0C] = &CPU::OP_0x0C;
    opcodeTable[0x0D] = &CPU::OP_0x0D;
    opcodeTable[0x0E] = &CPU::OP_0x0E;
    opcodeTable[0x0F] = &CPU::OP_0x0F;

    opcodeTable[0x10] = &CPU::OP_0x10;
    opcodeTable[0x11] = &CPU::OP_0x11;
    opcodeTable[0x12] = &CPU::OP_0x12;
    opcodeTable[0x13] = &CPU::OP_0x13;
    opcodeTable[0x14] = &CPU::OP_0x14;
    opcodeTable[0x15] = &CPU::OP_0x15;
    opcodeTable[0x16] = &CPU::OP_0x16;
    opcodeTable[0x17] = &CPU::OP_0x17;
    opcodeTable[0x18] = &CPU::OP_0x18;
    opcodeTable[0x19] = &CPU::OP_0x19;
    opcodeTable[0x1A] = &CPU::OP_0x1A;
    opcodeTable[0x1B] = &CPU::OP_0x1B;
    opcodeTable[0x1C] = &CPU::OP_0x1C;
    opcodeTable[0x1D] = &CPU::OP_0x1D;
    opcodeTable[0x1E] = &CPU::OP_0x1E;
    opcodeTable[0x1F] = &CPU::OP_0x1F;

    opcodeTable[0x20] = &CPU::OP_0x20;
    opcodeTable[0x21] = &CPU::OP_0x21;
    opcodeTable[0x22] = &CPU::OP_0x22;
    opcodeTable[0x23] = &CPU::OP_0x23;
    opcodeTable[0x24] = &CPU::OP_0x24;
    opcodeTable[0x25] = &CPU::OP_0x25;
    opcodeTable[0x26] = &CPU::OP_0x26;
    opcodeTable[0x27] = &CPU::OP_0x27;
    opcodeTable[0x28] = &CPU::OP_0x28;
    opcodeTable[0x29] = &CPU::OP_0x29;
    opcodeTable[0x2A] = &CPU::OP_0x2A;
    opcodeTable[0x2B] = &CPU::OP_0x2B;
    opcodeTable[0x2C] = &CPU::OP_0x2C;
    opcodeTable[0x2D] = &CPU::OP_0x2D;
    opcodeTable[0x2E] = &CPU::OP_0x2E;
    opcodeTable[0x2F] = &CPU::OP_0x2F;

    opcodeTable[0x30] = &CPU::OP_0x30;
    opcodeTable[0x31] = &CPU::OP_0x31;
    opcodeTable[0x32] = &CPU::OP_0x32;
    opcodeTable[0x33] = &CPU::OP_0x33;
    opcodeTable[0x34] = &CPU::OP_0x34;
    opcodeTable[0x35] = &CPU::OP_0x35;
    opcodeTable[0x36] = &CPU::OP_0x36;
    opcodeTable[0x37] = &CPU::OP_0x37;
    opcodeTable[0x38] = &CPU::OP_0x38;
    opcodeTable[0x39] = &CPU::OP_0x39;
    opcodeTable[0x3A] = &CPU::OP_0x3A;
    opcodeTable[0x3B] = &CPU::OP_0x3B;
    opcodeTable[0x3C] = &CPU::OP_0x3C;
    opcodeTable[0x3D] = &CPU::OP_0x3D;
    opcodeTable[0x3E] = &CPU::OP_0x3E;
    opcodeTable[0x3F] = &CPU::OP_0x3F;

    opcodeTable[0x40] = &CPU::OP_0x40;
    opcodeTable[0x41] = &CPU::OP_0x41;
    opcodeTable[0x42] = &CPU::OP_0x42;
    opcodeTable[0x43] = &CPU::OP_0x43;
    opcodeTable[0x44] = &CPU::OP_0x44;
    opcodeTable[0x45] = &CPU::OP_0x45;
    opcodeTable[0x46] = &CPU::OP_0x46;
    opcodeTable[0x47] = &CPU::OP_0x47;
    opcodeTable[0x48] = &CPU::OP_0x48;
    opcodeTable[0x49] = &CPU::OP_0x49;
    opcodeTable[0x4A] = &CPU::OP_0x4A;
    opcodeTable[0x4B] = &CPU::OP_0x4B;
    opcodeTable[0x4C] = &CPU::OP_0x4C;
    opcodeTable[0x4D] = &CPU::OP_0x4D;
    opcodeTable[0x4E] = &CPU::OP_0x4E;
    opcodeTable[0x4F] = &CPU::OP_0x4F;

    opcodeTable[0x50] = &CPU::OP_0x50;
    opcodeTable[0x51] = &CPU::OP_0x51;
    opcodeTable[0x52] = &CPU::OP_0x52;
    opcodeTable[0x53] = &CPU::OP_0x53;
    opcodeTable[0x54] = &CPU::OP_0x54;
    opcodeTable[0x55] = &CPU::OP_0x55;
    opcodeTable[0x56] = &CPU::OP_0x56;
    opcodeTable[0x57] = &CPU::OP_0x57;
    opcodeTable[0x58] = &CPU::OP_0x58;
    opcodeTable[0x59] = &CPU::OP_0x59;
    opcodeTable[0x5A] = &CPU::OP_0x5A;
    opcodeTable[0x5B] = &CPU::OP_0x5B;
    opcodeTable[0x5C] = &CPU::OP_0x5C;
    opcodeTable[0x5D] = &CPU::OP_0x5D;
    opcodeTable[0x5E] = &CPU::OP_0x5E;
    opcodeTable[0x5F] = &CPU::OP_0x5F;

    opcodeTable[0x60] = &CPU::OP_0x60;
    opcodeTable[0x61] = &CPU::OP_0x61;
    opcodeTable[0x62] = &CPU::OP_0x62;
    opcodeTable[0x63] = &CPU::OP_0x63;
    opcodeTable[0x64] = &CPU::OP_0x64;
    opcodeTable[0x65] = &CPU::OP_0x65;
    opcodeTable[0x66] = &CPU::OP_0x66;
    opcodeTable[0x67] = &CPU::OP_0x67;
    opcodeTable[0x68] = &CPU::OP_0x68;
    opcodeTable[0x69] = &CPU::OP_0x69;
    opcodeTable[0x6A] = &CPU::OP_0x6A;
    opcodeTable[0x6B] = &CPU::OP_0x6B;
    opcodeTable[0x6C] = &CPU::OP_0x6C;
    opcodeTable[0x6D] = &CPU::OP_0x6D;
    opcodeTable[0x6E] = &CPU::OP_0x6E;
    opcodeTable[0x6F] = &CPU::OP_0x6F;

    opcodeTable[0x70] = &CPU::OP_0x70;
    opcodeTable[0x71] = &CPU::OP_0x71;
    opcodeTable[0x72] = &CPU::OP_0x72;
    opcodeTable[0x73] = &CPU::OP_0x73;
    opcodeTable[0x74] = &CPU::OP_0x74;
    opcodeTable[0x75] = &CPU::OP_0x75;
    opcodeTable[0x76] = &CPU::OP_0x76;
    opcodeTable[0x77] = &CPU::OP_0x77;
    opcodeTable[0x78] = &CPU::OP_0x78;
    opcodeTable[0x79] = &CPU::OP_0x79;
    opcodeTable[0x7A] = &CPU::OP_0x7A;
    opcodeTable[0x7B] = &CPU::OP_0x7B;
    opcodeTable[0x7C] = &CPU::OP_0x7C;
    opcodeTable[0x7D] = &CPU::OP_0x7D;
    opcodeTable[0x7E] = &CPU::OP_0x7E;
    opcodeTable[0x7F] = &CPU::OP_0x7F;

    opcodeTable[0x80] = &CPU::OP_0x80;
    opcodeTable[0x81] = &CPU::OP_0x81;
    opcodeTable[0x82] = &CPU::OP_0x82;
    opcodeTable[0x83] = &CPU::OP_0x83;
    opcodeTable[0x84] = &CPU::OP_0x84;
    opcodeTable[0x85] = &CPU::OP_0x85;
    opcodeTable[0x86] = &CPU::OP_0x86;
    opcodeTable[0x87] = &CPU::OP_0x87;
    opcodeTable[0x88] = &CPU::OP_0x88;
    opcodeTable[0x89] = &CPU::OP_0x89;
    opcodeTable[0x8A] = &CPU::OP_0x8A;
    opcodeTable[0x8B] = &CPU::OP_0x8B;
    opcodeTable[0x8C] = &CPU::OP_0x8C;
    opcodeTable[0x8D] = &CPU::OP_0x8D;
    opcodeTable[0x8E] = &CPU::OP_0x8E;
    opcodeTable[0x8F] = &CPU::OP_0x8F;

    opcodeTable[0x90] = &CPU::OP_0x90;
    opcodeTable[0x91] = &CPU::OP_0x91;
    opcodeTable[0x92] = &CPU::OP_0x92;
    opcodeTable[0x93] = &CPU::OP_0x93;
    opcodeTable[0x94] = &CPU::OP_0x94;
    opcodeTable[0x95] = &CPU::OP_0x95;
    opcodeTable[0x96] = &CPU::OP_0x96;
    opcodeTable[0x97] = &CPU::OP_0x97;
    opcodeTable[0x98] = &CPU::OP_0x98;
    opcodeTable[0x99] = &CPU::OP_0x99;
    opcodeTable[0x9A] = &CPU::OP_0x9A;
    opcodeTable[0x9B] = &CPU::OP_0x9B;
    opcodeTable[0x9C] = &CPU::OP_0x9C;
    opcodeTable[0x9D] = &CPU::OP_0x9D;
    opcodeTable[0x9E] = &CPU::OP_0x9E;
    opcodeTable[0x9F] = &CPU::OP_0x9F;

    opcodeTable[0xA0] = &CPU::OP_0xA0;
    opcodeTable[0xA1] = &CPU::OP_0xA1;
    opcodeTable[0xA2] = &CPU::OP_0xA2;
    opcodeTable[0xA3] = &CPU::OP_0xA3;
    opcodeTable[0xA4] = &CPU::OP_0xA4;
    opcodeTable[0xA5] = &CPU::OP_0xA5;
    opcodeTable[0xA6] = &CPU::OP_0xA6;
    opcodeTable[0xA7] = &CPU::OP_0xA7;
    opcodeTable[0xA8] = &CPU::OP_0xA8;
    opcodeTable[0xA9] = &CPU::OP_0xA9;
    opcodeTable[0xAA] = &CPU::OP_0xAA;
    opcodeTable[0xAB] = &CPU::OP_0xAB;
    opcodeTable[0xAC] = &CPU::OP_0xAC;
    opcodeTable[0xAD] = &CPU::OP_0xAD;
    opcodeTable[0xAE] = &CPU::OP_0xAE;
    opcodeTable[0xAF] = &CPU::OP_0xAF;

    opcodeTable[0xB0] = &CPU::OP_0xB0;
    opcodeTable[0xB1] = &CPU::OP_0xB1;
    opcodeTable[0xB2] = &CPU::OP_0xB2;
    opcodeTable[0xB3] = &CPU::OP_0xB3;
    opcodeTable[0xB4] = &CPU::OP_0xB4;
    opcodeTable[0xB5] = &CPU::OP_0xB5;
    opcodeTable[0xB6] = &CPU::OP_0xB6;
    opcodeTable[0xB7] = &CPU::OP_0xB7;
    opcodeTable[0xB8] = &CPU::OP_0xB8;
    opcodeTable[0xB9] = &CPU::OP_0xB9;
    opcodeTable[0xBA] = &CPU::OP_0xBA;
    opcodeTable[0xBB] = &CPU::OP_0xBB;
    opcodeTable[0xBC] = &CPU::OP_0xBC;
    opcodeTable[0xBD] = &CPU::OP_0xBD;
    opcodeTable[0xBE] = &CPU::OP_0xBE;
    opcodeTable[0xBF] = &CPU::OP_0xBF;

    opcodeTable[0xC0] = &CPU::OP_0xC0;
    opcodeTable[0xC1] = &CPU::OP_0xC1;
    opcodeTable[0xC2] = &CPU::OP_0xC2;
    opcodeTable[0xC3] = &CPU::OP_0xC3;
    opcodeTable[0xC4] = &CPU::OP_0xC4;
    opcodeTable[0xC5] = &CPU::OP_0xC5;
    opcodeTable[0xC6] = &CPU::OP_0xC6;
    opcodeTable[0xC7] = &CPU::OP_0xC7;
    opcodeTable[0xC8] = &CPU::OP_0xC8;
    opcodeTable[0xC9] = &CPU::OP_0xC9;
    opcodeTable[0xCA] = &CPU::OP_0xCA;
    opcodeTable[0xCB] = &CPU::OP_NULL;
    opcodeTable[0xCC] = &CPU::OP_0xCC;
    opcodeTable[0xCD] = &CPU::OP_0xCD;
    opcodeTable[0xCE] = &CPU::OP_0xCE;
    opcodeTable[0xCF] = &CPU::OP_0xCF;

    opcodeTable[0xD0] = &CPU::OP_0xD0;
    opcodeTable[0xD1] = &CPU::OP_0xD1;
    opcodeTable[0xD2] = &CPU::OP_0xD2;
    opcodeTable[0xD3] = &CPU::OP_NULL;
    opcodeTable[0xD4] = &CPU::OP_0xD4;
    opcodeTable[0xD5] = &CPU::OP_0xD5;
    opcodeTable[0xD6] = &CPU::OP_0xD6;
    opcodeTable[0xD7] = &CPU::OP_0xD7;
    opcodeTable[0xD8] = &CPU::OP_0xD8;
    opcodeTable[0xD9] = &CPU::OP_0xD9;
    opcodeTable[0xDA] = &CPU::OP_0xDA;
    opcodeTable[0xDB] = &CPU::OP_NULL;
    opcodeTable[0xDC] = &CPU::OP_0xDC;
    opcodeTable[0xDD] = &CPU::OP_NULL;
    opcodeTable[0xDE] = &CPU::OP_0xDE;
    opcodeTable[0xDF] = &CPU::OP_0xDF;

    opcodeTable[0xE0] = &CPU::OP_0xE0;
    opcodeTable[0xE1] = &CPU::OP_0xE1;
    opcodeTable[0xE2] = &CPU::OP_0xE2;
    opcodeTable[0xE3] = &CPU::OP_NULL;
    opcodeTable[0xE4] = &CPU::OP_NULL;
    opcodeTable[0xE5] = &CPU::OP_0xE5;
    opcodeTable[0xE6] = &CPU::OP_0xE6;
    opcodeTable[0xE7] = &CPU::OP_0xE7;
    opcodeTable[0xE8] = &CPU::OP_0xE8;
    opcodeTable[0xE9] = &CPU::OP_0xE9;
    opcodeTable[0xEA] = &CPU::OP_0xEA;
    opcodeTable[0xEB] = &CPU::OP_NULL;
    opcodeTable[0xEC] = &CPU::OP_NULL;
    opcodeTable[0xED] = &CPU::OP_NULL;
    opcodeTable[0xEE] = &CPU::OP_0xEE;
    opcodeTable[0xEF] = &CPU::OP_0xEF;

    opcodeTable[0xF0] = &CPU::OP_0xF0;
    opcodeTable[0xF1] = &CPU::OP_0xF1;
    opcodeTable[0xF2] = &CPU::OP_0xF2;
    opcodeTable[0xF3] = &CPU::OP_0xF3;
    opcodeTable[0xF4] = &CPU::OP_NULL;
    opcodeTable[0xF5] = &CPU::OP_0xF5;
    opcodeTable[0xF6] = &CPU::OP_0xF6;
    opcodeTable[0xF7] = &CPU::OP_0xF7;
    opcodeTable[0xF8] = &CPU::OP_0xF8;
    opcodeTable[0xF9] = &CPU::OP_0xF9;
    opcodeTable[0xFA] = &CPU::OP_0xFA;
    opcodeTable[0xFB] = &CPU::OP_0xFB;
    opcodeTable[0xFC] = &CPU::OP_NULL;
    opcodeTable[0xFD] = &CPU::OP_NULL;
    opcodeTable[0xFE] = &CPU::OP_0xFE;
    opcodeTable[0xFF] = &CPU::OP_0xFF;

    CBopcodeTable[0x00] = &CPU::OP_0xCB00;
    CBopcodeTable[0x01] = &CPU::OP_0xCB01;
    CBopcodeTable[0x02] = &CPU::OP_0xCB02;
    CBopcodeTable[0x03] = &CPU::OP_0xCB03;
    CBopcodeTable[0x04] = &CPU::OP_0xCB04;
    CBopcodeTable[0x05] = &CPU::OP_0xCB05;
    CBopcodeTable[0x06] = &CPU::OP_0xCB06;
    CBopcodeTable[0x07] = &CPU::OP_0xCB07;
    CBopcodeTable[0x08] = &CPU::OP_0xCB08;
    CBopcodeTable[0x09] = &CPU::OP_0xCB09;
    CBopcodeTable[0x0A] = &CPU::OP_0xCB0A;
    CBopcodeTable[0x0B] = &CPU::OP_0xCB0B;
    CBopcodeTable[0x0C] = &CPU::OP_0xCB0C;
    CBopcodeTable[0x0D] = &CPU::OP_0xCB0D;
    CBopcodeTable[0x0E] = &CPU::OP_0xCB0E;
    CBopcodeTable[0x0F] = &CPU::OP_0xCB0F;

    CBopcodeTable[0x10] = &CPU::OP_0xCB10;
    CBopcodeTable[0x11] = &CPU::OP_0xCB11;
    CBopcodeTable[0x12] = &CPU::OP_0xCB12;
    CBopcodeTable[0x13] = &CPU::OP_0xCB13;
    CBopcodeTable[0x14] = &CPU::OP_0xCB14;
    CBopcodeTable[0x15] = &CPU::OP_0xCB15;
    CBopcodeTable[0x16] = &CPU::OP_0xCB16;
    CBopcodeTable[0x17] = &CPU::OP_0xCB17;
    CBopcodeTable[0x18] = &CPU::OP_0xCB18;
    CBopcodeTable[0x19] = &CPU::OP_0xCB19;
    CBopcodeTable[0x1A] = &CPU::OP_0xCB1A;
    CBopcodeTable[0x1B] = &CPU::OP_0xCB1B;
    CBopcodeTable[0x1C] = &CPU::OP_0xCB1C;
    CBopcodeTable[0x1D] = &CPU::OP_0xCB1D;
    CBopcodeTable[0x1E] = &CPU::OP_0xCB1E;
    CBopcodeTable[0x1F] = &CPU::OP_0xCB1F;

    CBopcodeTable[0x20] = &CPU::OP_0xCB20;
    CBopcodeTable[0x21] = &CPU::OP_0xCB21;
    CBopcodeTable[0x22] = &CPU::OP_0xCB22;
    CBopcodeTable[0x23] = &CPU::OP_0xCB23;
    CBopcodeTable[0x24] = &CPU::OP_0xCB24;
    CBopcodeTable[0x25] = &CPU::OP_0xCB25;
    CBopcodeTable[0x26] = &CPU::OP_0xCB26;
    CBopcodeTable[0x27] = &CPU::OP_0xCB27;
    CBopcodeTable[0x28] = &CPU::OP_0xCB28;
    CBopcodeTable[0x29] = &CPU::OP_0xCB29;
    CBopcodeTable[0x2A] = &CPU::OP_0xCB2A;
    CBopcodeTable[0x2B] = &CPU::OP_0xCB2B;
    CBopcodeTable[0x2C] = &CPU::OP_0xCB2C;
    CBopcodeTable[0x2D] = &CPU::OP_0xCB2D;
    CBopcodeTable[0x2E] = &CPU::OP_0xCB2E;
    CBopcodeTable[0x2F] = &CPU::OP_0xCB2F;

    CBopcodeTable[0x30] = &CPU::OP_0xCB30;
    CBopcodeTable[0x31] = &CPU::OP_0xCB31;
    CBopcodeTable[0x32] = &CPU::OP_0xCB32;
    CBopcodeTable[0x33] = &CPU::OP_0xCB33;
    CBopcodeTable[0x34] = &CPU::OP_0xCB34;
    CBopcodeTable[0x35] = &CPU::OP_0xCB35;
    CBopcodeTable[0x36] = &CPU::OP_0xCB36;
    CBopcodeTable[0x37] = &CPU::OP_0xCB37;
    CBopcodeTable[0x38] = &CPU::OP_0xCB38;
    CBopcodeTable[0x39] = &CPU::OP_0xCB39;
    CBopcodeTable[0x3A] = &CPU::OP_0xCB3A;
    CBopcodeTable[0x3B] = &CPU::OP_0xCB3B;
    CBopcodeTable[0x3C] = &CPU::OP_0xCB3C;
    CBopcodeTable[0x3D] = &CPU::OP_0xCB3D;
    CBopcodeTable[0x3E] = &CPU::OP_0xCB3E;
    CBopcodeTable[0x3F] = &CPU::OP_0xCB3F;

    CBopcodeTable[0x40] = &CPU::OP_0xCB40;
    CBopcodeTable[0x41] = &CPU::OP_0xCB41;
    CBopcodeTable[0x42] = &CPU::OP_0xCB42;
    CBopcodeTable[0x43] = &CPU::OP_0xCB43;
    CBopcodeTable[0x44] = &CPU::OP_0xCB44;
    CBopcodeTable[0x45] = &CPU::OP_0xCB45;
    CBopcodeTable[0x46] = &CPU::OP_0xCB46;
    CBopcodeTable[0x47] = &CPU::OP_0xCB47;
    CBopcodeTable[0x48] = &CPU::OP_0xCB48;
    CBopcodeTable[0x49] = &CPU::OP_0xCB49;
    CBopcodeTable[0x4A] = &CPU::OP_0xCB4A;
    CBopcodeTable[0x4B] = &CPU::OP_0xCB4B;
    CBopcodeTable[0x4C] = &CPU::OP_0xCB4C;
    CBopcodeTable[0x4D] = &CPU::OP_0xCB4D;
    CBopcodeTable[0x4E] = &CPU::OP_0xCB4E;
    CBopcodeTable[0x4F] = &CPU::OP_0xCB4F;

    CBopcodeTable[0x50] = &CPU::OP_0xCB50;
    CBopcodeTable[0x51] = &CPU::OP_0xCB51;
    CBopcodeTable[0x52] = &CPU::OP_0xCB52;
    CBopcodeTable[0x53] = &CPU::OP_0xCB53;
    CBopcodeTable[0x54] = &CPU::OP_0xCB54;
    CBopcodeTable[0x55] = &CPU::OP_0xCB55;
    CBopcodeTable[0x56] = &CPU::OP_0xCB56;
    CBopcodeTable[0x57] = &CPU::OP_0xCB57;
    CBopcodeTable[0x58] = &CPU::OP_0xCB58;
    CBopcodeTable[0x59] = &CPU::OP_0xCB59;
    CBopcodeTable[0x5A] = &CPU::OP_0xCB5A;
    CBopcodeTable[0x5B] = &CPU::OP_0xCB5B;
    CBopcodeTable[0x5C] = &CPU::OP_0xCB5C;
    CBopcodeTable[0x5D] = &CPU::OP_0xCB5D;
    CBopcodeTable[0x5E] = &CPU::OP_0xCB5E;
    CBopcodeTable[0x5F] = &CPU::OP_0xCB5F;

    CBopcodeTable[0x60] = &CPU::OP_0xCB60;
    CBopcodeTable[0x61] = &CPU::OP_0xCB61;
    CBopcodeTable[0x62] = &CPU::OP_0xCB62;
    CBopcodeTable[0x63] = &CPU::OP_0xCB63;
    CBopcodeTable[0x64] = &CPU::OP_0xCB64;
    CBopcodeTable[0x65] = &CPU::OP_0xCB65;
    CBopcodeTable[0x66] = &CPU::OP_0xCB66;
    CBopcodeTable[0x67] = &CPU::OP_0xCB67;
    CBopcodeTable[0x68] = &CPU::OP_0xCB68;
    CBopcodeTable[0x69] = &CPU::OP_0xCB69;
    CBopcodeTable[0x6A] = &CPU::OP_0xCB6A;
    CBopcodeTable[0x6B] = &CPU::OP_0xCB6B;
    CBopcodeTable[0x6C] = &CPU::OP_0xCB6C;
    CBopcodeTable[0x6D] = &CPU::OP_0xCB6D;
    CBopcodeTable[0x6E] = &CPU::OP_0xCB6E;
    CBopcodeTable[0x6F] = &CPU::OP_0xCB6F;

    CBopcodeTable[0x70] = &CPU::OP_0xCB70;
    CBopcodeTable[0x71] = &CPU::OP_0xCB71;
    CBopcodeTable[0x72] = &CPU::OP_0xCB72;
    CBopcodeTable[0x73] = &CPU::OP_0xCB73;
    CBopcodeTable[0x74] = &CPU::OP_0xCB74;
    CBopcodeTable[0x75] = &CPU::OP_0xCB75;
    CBopcodeTable[0x76] = &CPU::OP_0xCB76;
    CBopcodeTable[0x77] = &CPU::OP_0xCB77;
    CBopcodeTable[0x78] = &CPU::OP_0xCB78;
    CBopcodeTable[0x79] = &CPU::OP_0xCB79;
    CBopcodeTable[0x7A] = &CPU::OP_0xCB7A;
    CBopcodeTable[0x7B] = &CPU::OP_0xCB7B;
    CBopcodeTable[0x7C] = &CPU::OP_0xCB7C;
    CBopcodeTable[0x7D] = &CPU::OP_0xCB7D;
    CBopcodeTable[0x7E] = &CPU::OP_0xCB7E;
    CBopcodeTable[0x7F] = &CPU::OP_0xCB7F;

    CBopcodeTable[0x80] = &CPU::OP_0xCB80;
    CBopcodeTable[0x81] = &CPU::OP_0xCB81;
    CBopcodeTable[0x82] = &CPU::OP_0xCB82;
    CBopcodeTable[0x83] = &CPU::OP_0xCB83;
    CBopcodeTable[0x84] = &CPU::OP_0xCB84;
    CBopcodeTable[0x85] = &CPU::OP_0xCB85;
    CBopcodeTable[0x86] = &CPU::OP_0xCB86;
    CBopcodeTable[0x87] = &CPU::OP_0xCB87;
    CBopcodeTable[0x88] = &CPU::OP_0xCB88;
    CBopcodeTable[0x89] = &CPU::OP_0xCB89;
    CBopcodeTable[0x8A] = &CPU::OP_0xCB8A;
    CBopcodeTable[0x8B] = &CPU::OP_0xCB8B;
    CBopcodeTable[0x8C] = &CPU::OP_0xCB8C;
    CBopcodeTable[0x8D] = &CPU::OP_0xCB8D;
    CBopcodeTable[0x8E] = &CPU::OP_0xCB8E;
    CBopcodeTable[0x8F] = &CPU::OP_0xCB8F;

    CBopcodeTable[0x90] = &CPU::OP_0xCB90;
    CBopcodeTable[0x91] = &CPU::OP_0xCB91;
    CBopcodeTable[0x92] = &CPU::OP_0xCB92;
    CBopcodeTable[0x93] = &CPU::OP_0xCB93;
    CBopcodeTable[0x94] = &CPU::OP_0xCB94;
    CBopcodeTable[0x95] = &CPU::OP_0xCB95;
    CBopcodeTable[0x96] = &CPU::OP_0xCB96;
    CBopcodeTable[0x97] = &CPU::OP_0xCB97;
    CBopcodeTable[0x98] = &CPU::OP_0xCB98;
    CBopcodeTable[0x99] = &CPU::OP_0xCB99;
    CBopcodeTable[0x9A] = &CPU::OP_0xCB9A;
    CBopcodeTable[0x9B] = &CPU::OP_0xCB9B;
    CBopcodeTable[0x9C] = &CPU::OP_0xCB9C;
    CBopcodeTable[0x9D] = &CPU::OP_0xCB9D;
    CBopcodeTable[0x9E] = &CPU::OP_0xCB9E;
    CBopcodeTable[0x9F] = &CPU::OP_0xCB9F;

    CBopcodeTable[0xA0] = &CPU::OP_0xCBA0;
    CBopcodeTable[0xA1] = &CPU::OP_0xCBA1;
    CBopcodeTable[0xA2] = &CPU::OP_0xCBA2;
    CBopcodeTable[0xA3] = &CPU::OP_0xCBA3;
    CBopcodeTable[0xA4] = &CPU::OP_0xCBA4;
    CBopcodeTable[0xA5] = &CPU::OP_0xCBA5;
    CBopcodeTable[0xA6] = &CPU::OP_0xCBA6;
    CBopcodeTable[0xA7] = &CPU::OP_0xCBA7;
    CBopcodeTable[0xA8] = &CPU::OP_0xCBA8;
    CBopcodeTable[0xA9] = &CPU::OP_0xCBA9;
    CBopcodeTable[0xAA] = &CPU::OP_0xCBAA;
    CBopcodeTable[0xAB] = &CPU::OP_0xCBAB;
    CBopcodeTable[0xAC] = &CPU::OP_0xCBAC;
    CBopcodeTable[0xAD] = &CPU::OP_0xCBAD;
    CBopcodeTable[0xAE] = &CPU::OP_0xCBAE;
    CBopcodeTable[0xAF] = &CPU::OP_0xCBAF;

    CBopcodeTable[0xB0] = &CPU::OP_0xCBB0;
    CBopcodeTable[0xB1] = &CPU::OP_0xCBB1;
    CBopcodeTable[0xB2] = &CPU::OP_0xCBB2;
    CBopcodeTable[0xB3] = &CPU::OP_0xCBB3;
    CBopcodeTable[0xB4] = &CPU::OP_0xCBB4;
    CBopcodeTable[0xB5] = &CPU::OP_0xCBB5;
    CBopcodeTable[0xB6] = &CPU::OP_0xCBB6;
    CBopcodeTable[0xB7] = &CPU::OP_0xCBB7;
    CBopcodeTable[0xB8] = &CPU::OP_0xCBB8;
    CBopcodeTable[0xB9] = &CPU::OP_0xCBB9;
    CBopcodeTable[0xBA] = &CPU::OP_0xCBBA;
    CBopcodeTable[0xBB] = &CPU::OP_0xCBBB;
    CBopcodeTable[0xBC] = &CPU::OP_0xCBBC;
    CBopcodeTable[0xBD] = &CPU::OP_0xCBBD;
    CBopcodeTable[0xBE] = &CPU::OP_0xCBBE;
    CBopcodeTable[0xBF] = &CPU::OP_0xCBBF;

    CBopcodeTable[0xC0] = &CPU::OP_0xCBC0;
    CBopcodeTable[0xC1] = &CPU::OP_0xCBC1;
    CBopcodeTable[0xC2] = &CPU::OP_0xCBC2;
    CBopcodeTable[0xC3] = &CPU::OP_0xCBC3;
    CBopcodeTable[0xC4] = &CPU::OP_0xCBC4;
    CBopcodeTable[0xC5] = &CPU::OP_0xCBC5;
    CBopcodeTable[0xC6] = &CPU::OP_0xCBC6;
    CBopcodeTable[0xC7] = &CPU::OP_0xCBC7;
    CBopcodeTable[0xC8] = &CPU::OP_0xCBC8;
    CBopcodeTable[0xC9] = &CPU::OP_0xCBC9;
    CBopcodeTable[0xCA] = &CPU::OP_0xCBCA;
    CBopcodeTable[0xCB] = &CPU::OP_0xCBCB;
    CBopcodeTable[0xCC] = &CPU::OP_0xCBCC;
    CBopcodeTable[0xCD] = &CPU::OP_0xCBCD;
    CBopcodeTable[0xCE] = &CPU::OP_0xCBCE;
    CBopcodeTable[0xCF] = &CPU::OP_0xCBCF;

    CBopcodeTable[0xD0] = &CPU::OP_0xCBD0;
    CBopcodeTable[0xD1] = &CPU::OP_0xCBD1;
    CBopcodeTable[0xD2] = &CPU::OP_0xCBD2;
    CBopcodeTable[0xD3] = &CPU::OP_0xCBD3;
    CBopcodeTable[0xD4] = &CPU::OP_0xCBD4;
    CBopcodeTable[0xD5] = &CPU::OP_0xCBD5;
    CBopcodeTable[0xD6] = &CPU::OP_0xCBD6;
    CBopcodeTable[0xD7] = &CPU::OP_0xCBD7;
    CBopcodeTable[0xD8] = &CPU::OP_0xCBD8;
    CBopcodeTable[0xD9] = &CPU::OP_0xCBD9;
    CBopcodeTable[0xDA] = &CPU::OP_0xCBDA;
    CBopcodeTable[0xDB] = &CPU::OP_0xCBDB;
    CBopcodeTable[0xDC] = &CPU::OP_0xCBDC;
    CBopcodeTable[0xDD] = &CPU::OP_0xCBDD;
    CBopcodeTable[0xDE] = &CPU::OP_0xCBDE;
    CBopcodeTable[0xDF] = &CPU::OP_0xCBDF;

    CBopcodeTable[0xE0] = &CPU::OP_0xCBE0;
    CBopcodeTable[0xE1] = &CPU::OP_0xCBE1;
    CBopcodeTable[0xE2] = &CPU::OP_0xCBE2;
    CBopcodeTable[0xE3] = &CPU::OP_0xCBE3;
    CBopcodeTable[0xE4] = &CPU::OP_0xCBE4;
    CBopcodeTable[0xE5] = &CPU::OP_0xCBE5;
    CBopcodeTable[0xE6] = &CPU::OP_0xCBE6;
    CBopcodeTable[0xE7] = &CPU::OP_0xCBE7;
    CBopcodeTable[0xE8] = &CPU::OP_0xCBE8;
    CBopcodeTable[0xE9] = &CPU::OP_0xCBE9;
    CBopcodeTable[0xEA] = &CPU::OP_0xCBEA;
    CBopcodeTable[0xEB] = &CPU::OP_0xCBEB;
    CBopcodeTable[0xEC] = &CPU::OP_0xCBEC;
    CBopcodeTable[0xED] = &CPU::OP_0xCBED;
    CBopcodeTable[0xEE] = &CPU::OP_0xCBEE;
    CBopcodeTable[0xEF] = &CPU::OP_0xCBEF;

    CBopcodeTable[0xF0] = &CPU::OP_0xCBF0;
    CBopcodeTable[0xF1] = &CPU::OP_0xCBF1;
    CBopcodeTable[0xF2] = &CPU::OP_0xCBF2;
    CBopcodeTable[0xF3] = &CPU::OP_0xCBF3;
    CBopcodeTable[0xF4] = &CPU::OP_0xCBF4;
    CBopcodeTable[0xF5] = &CPU::OP_0xCBF5;
    CBopcodeTable[0xF6] = &CPU::OP_0xCBF6;
    CBopcodeTable[0xF7] = &CPU::OP_0xCBF7;
    CBopcodeTable[0xF8] = &CPU::OP_0xCBF8;
    CBopcodeTable[0xF9] = &CPU::OP_0xCBF9;
    CBopcodeTable[0xFA] = &CPU::OP_0xCBFA;
    CBopcodeTable[0xFB] = &CPU::OP_0xCBFB;
    CBopcodeTable[0xFC] = &CPU::OP_0xCBFC;
    CBopcodeTable[0xFD] = &CPU::OP_0xCBFD;
    CBopcodeTable[0xFE] = &CPU::OP_0xCBFE;
    CBopcodeTable[0xFF] = &CPU::OP_0xCBFF;

}

// OPCODES

// OP_[ROW][COLUMN]
// Ex. x7 (row) xA (column) = OP_0x7A

uint8_t CPU::OP_0x00() {
    return 1;
}

//Load the 2 bytes of immediate data into register pair BC.
uint8_t CPU::OP_0x01() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    bc.reg16 = (highByte << 8u) | lowByte;
    return 3;
}

//Store the contents of register A in the memory location specified by register pair BC.
uint8_t CPU::OP_0x02() {
    write(bc.reg16, af.a);
    return 2;
}

//Increment the contents of register pair BC by 1.
uint8_t CPU::OP_0x03() {
    bc.reg16++;
    return 2;
}

//Increment the contents of register B by 1.
uint8_t CPU::OP_0x04(){
    uint8_t old = bc.b;
    bc.b++;
    setFlag('Z', bc.b==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register B by 1.
uint8_t CPU::OP_0x05(){
    uint8_t old = bc.b;
    bc.b--;
    setFlag('Z', bc.b==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register B.
uint8_t CPU::OP_0x06(){
    bc.b = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the left
uint8_t CPU::OP_0x07() {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (af.a & 0x80) >> 7u;
    //shift left
    af.a = af.a << 1u;
    //set bit 0 to old bit 7
    af.a |= oldBit7;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit7 == 0x01);

    return 1;
}

//Store lower byte of SP in address of 16bit immediate, higher in imm+1
uint8_t CPU::OP_0x08() {
    uint16_t newAddress = read(++pc);
    newAddress |= (read(++pc) << 8u);

    uint8_t spLower = (sp & 0x00FF);
    uint8_t spHigher = (sp & 0xFF00) >> 8u;

    write(newAddress, spLower);
    write(newAddress+1, spHigher);

    return 5;
}

//stores hl + bc in hl
uint8_t CPU::OP_0x09() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 = oldHl + bc.reg16;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (bc.reg16 & 0x0FFF)) > 0x0FFF);
    setFlag('C', (oldHl + bc.reg16) > 0xFFFF);
    return 2;
}

//store memory[bc] in a
uint8_t CPU::OP_0x0A() {
    af.a = read(bc.reg16);
    return 2;
}

//decrement bc by 1
uint8_t CPU::OP_0x0B() {
    bc.reg16--;
    return 2;
}

//increment register c by 1
uint8_t CPU::OP_0x0C() {
    uint8_t old = bc.c;
    bc.c++;
    setFlag('Z', bc.c == 0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register C by 1.
uint8_t CPU::OP_0x0D(){
    uint8_t old = bc.c;
    bc.c--;
    setFlag('Z', bc.c==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into c
uint8_t CPU::OP_0x0E(){
    bc.c = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the right
uint8_t CPU::OP_0x0F() {
    uint8_t oldBit0 = (af.a & 0x01) << 7u;
    af.a = af.a >> 1u;
    af.a |= oldBit0;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit0 == 0x80);

    return 1;
}

//STOP FUNCTION
// when exiting 'stop', incremement pc twice because two byte instruction ( 0x 10 00)
uint8_t CPU::OP_0x10() {
    pc++;
    stopped = true;
    return 1;
}

//load the next two bytes into de
uint8_t CPU::OP_0x11() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    de.reg16 = (highByte << 8u) | lowByte;
    return 3;
}

//store contents of register a in memory location specified by de
uint8_t CPU::OP_0x12() {
    uint16_t memoryLocation = de.reg16;
    write(memoryLocation, af.a);
    return 2;
}

//Increment the contents of register pair DE by 1.
uint8_t CPU::OP_0x13() {
    de.reg16++;
    return 2;
}

//Increment the contents of register D by 1.
uint8_t CPU::OP_0x14(){
    uint8_t old = de.d;
    de.d++;
    setFlag('Z', de.d==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register D by 1.
uint8_t CPU::OP_0x15(){
    uint8_t old = de.d;
    de.d--;
    setFlag('Z', de.d==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into d
uint8_t CPU::OP_0x16(){
    de.d = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the left through the carry flag
uint8_t CPU::OP_0x17() {
    //puts the old bit in the 0th bit spot
    uint8_t oldBit7 = (af.a & 0x80) >> 7u;
    //shift left
    af.a = af.a << 1u;
    //set bit 0 to carry flag
    af.a |= ((af.f & FLAG_C) >> 4u);

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit7 == 0x01);

    return 1;
}

//Jump s8 steps from the current address in the program counter (PC). (Jump relative.)
uint8_t CPU::OP_0x18() {
    auto jumpSteps = static_cast<int8_t>(read(++pc));
    pc += jumpSteps;
    return 3;
}

// Add the contents of register pair DE to the contents of register pair HL, and store the results in register pair HL.
uint8_t CPU::OP_0x19() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 += de.reg16;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (de.reg16 & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHl) + static_cast<uint32_t>(de.reg16)) > 0xFFFF);
    return 2;
}

//Load the 8-bit contents of memory specified by register pair DE into register A.
uint8_t CPU::OP_0x1A() {
    af.a = read(de.reg16);
    return 2;
}

//decrement de by 1
uint8_t CPU::OP_0x1B() {
    de.reg16--;
    return 2;
}

//increment register e's contents by 1
uint8_t CPU::OP_0x1C(){
    uint8_t old = de.e;
    de.e++;
    setFlag('Z', de.e==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register e by 1.
uint8_t CPU::OP_0x1D(){
    uint8_t old = de.e;
    de.e--;
    setFlag('Z', de.e==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//load immediate into e
uint8_t CPU::OP_0x1E(){
    de.e = read(++pc);
    return 2;
}

//Rotate the contents of Register A to the right through the carry flag
uint8_t CPU::OP_0x1F() {
    //gets old 0 bit
    uint8_t oldBit0 = (af.a & 0x01);
    //shift right
    af.a = af.a >> 1u;
    //set bit 7 to carry flag
    af.a |= ((af.f & FLAG_C) << 3u);

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', oldBit0 == 0x01);

    return 1;
}

// ROW x2

//if z flag is 0,jump (immediate s8) steps from the current address. otherwise, go to the end of the instruction
uint8_t CPU::OP_0x20() {
    if (!readFlag('Z')) {
        auto jumpSteps = static_cast<int8_t>(read(++pc));
        pc += jumpSteps;
        return 3;
    }
    pc++;
    return 2;
}


//Load the 2 bytes of immediate data into register pair HL.
uint8_t CPU::OP_0x21() {
    uint8_t low = read(++pc);
    uint8_t high = read(++pc);
    hl.h = high;
    hl.l = low;
    return 3;
}

//Store the contents of register A into the memory location specified by register pair HL, and simultaneously increment the contents of HL.
uint8_t CPU::OP_0x22() {
    write(hl.reg16, af.a);
    hl.reg16++;
    return 2;
}

//Increment the contents of register pair HL by 1.
uint8_t CPU::OP_0x23() {
    hl.reg16++;
    return 2;
}

//Increment the contents of register H by 1.
uint8_t CPU::OP_0x24(){
    uint8_t oldh = hl.h;
    hl.h++;
    setFlag('Z', hl.h==0);
    setFlag('N', false);
    setFlag('H', ((oldh & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register H by 1.
uint8_t CPU::OP_0x25() {
    uint8_t oldh = hl.h;
    hl.h--;
    setFlag('Z', hl.h==0);
    setFlag('N', true);
    setFlag('H', (oldh & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register H.
uint8_t CPU::OP_0x26() {
    pc++;
    hl.h = read(pc);
    return 2;
}

// Adjust the accumulator (register A) to a binary-coded decimal (BCD) number after BCD addition and subtraction operations.
// turns A from hex to decimal coded binary
// Ex. 0x0F (15 in decimal) becomes 0x15 (visually 15)
uint8_t CPU::OP_0x27() {
    uint8_t oldA = af.a;

    if (!readFlag('N')) { // last op was addition
        if (readFlag('C') || af.a > 0x99) {
            oldA += 0x60;
            setFlag('C', true);
        }
        if (readFlag('H') || (af.a & 0x0F) > 0x09) {
            oldA += 0x06;
        }
    } else { // last op was subtraction
        if (readFlag('C')) { oldA -= 0x60; }
        if (readFlag('H')) { oldA -= 0x06; }
    }

    af.a = oldA;

    setFlag('Z', oldA == 0);
    setFlag('H', false);
    return 1;
}

//If the Z flag is 1, jump s8 steps from the current address stored in the pc
uint8_t CPU::OP_0x28() {
    auto jumpSteps = static_cast<int8_t>(read(++pc));
    // if z flag is 1
    if (readFlag('Z')) {
        pc += jumpSteps;
        return 3;
    }
    return 2;
}

// Add the contents of register pair HL to the contents of register pair HL, and store the results in register pair HL.
uint8_t CPU::OP_0x29() {
    uint16_t  oldHL = hl.reg16;
    hl.reg16 += hl.reg16;

    setFlag('N', false);
    setFlag('H', ((oldHL & 0x0FFF) + (oldHL & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHL) + static_cast<uint32_t>(oldHL)) > 0xFFFF);
    return 2;
}

// Load the contents of memory specified by register pair HL into register A, and simultaneously increment the contents of HL.
uint8_t CPU::OP_0x2A() {
    af.a = read(hl.reg16);
    hl.reg16++;
    return 2;
}

// Decrement the contents of register pair HL by 1.
uint8_t CPU::OP_0x2B() {
    hl.reg16--;
    return 2;
}

//Increment the contents of register L by 1.
uint8_t CPU::OP_0x2C() {
    uint8_t oldL = hl.l;
    hl.l++;
    setFlag('Z', hl.l==0);
    setFlag('N', false);
    setFlag('H', ((oldL & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//Decrement the contents of register L by 1.
uint8_t CPU::OP_0x2D() {
    uint8_t oldL = hl.l;
    hl.l--;
    setFlag('Z', hl.l==0);
    setFlag('N', true);
    setFlag('H', (oldL & 0x0F) == 0x00);
    return 1;
}

// Load the 8-bit immediate operand d8 into register L.
uint8_t CPU::OP_0x2E() {
    pc++;
    hl.l = read(pc);
    return 2;
}

// Take the one's complement (i.e., flip all bits) of the contents of register A
uint8_t CPU::OP_0x2F() {
    af.a = ~af.a;
    setFlag('N', true);
    setFlag('H', true);
    return 1;
}


// ROW x3
//if c flag is 0,jump (immediate s8) steps from the current address. otherwise, go to the end of the instruction
uint8_t CPU::OP_0x30() {
    if (!readFlag('C')) {
        auto jumpSteps = static_cast<int8_t>(read(++pc));
        pc += jumpSteps;
        //decrement since we will increment right after the instruction
        return 3;
    }
    pc++;
    return 2;
}

//load the two bytes of immediate data into SP
uint8_t CPU::OP_0x31() {
    uint8_t lowByte = read(++pc);
    uint8_t highByte = read(++pc);
    sp = (highByte << 8u) | lowByte;
    return 3;
}

//write the contents of register A into the location specified by hl
uint8_t CPU::OP_0x32() {
    write(hl.reg16, af.a);
    hl.reg16--;
    return 2;
}

//increment sp by 1
uint8_t CPU::OP_0x33() {
    sp++;
    return 2;
}

//increment HL by 1
uint8_t CPU::OP_0x34() {
    uint8_t oldHl = read(hl.reg16);
    write(hl.reg16, oldHl+1);
    uint8_t newHl = oldHl+1;
    setFlag('Z', newHl == 0);
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 3;
}

//decrement memory at HL by 1
uint8_t CPU::OP_0x35() {
    uint8_t oldHl = read(hl.reg16);
    write(hl.reg16, oldHl-1);
    uint8_t newHl = oldHl-1;
    setFlag('Z', newHl == 0);
    setFlag('N', true);
    setFlag('H', (oldHl & 0x0F) == 0x00);
    return 3;
}

//load the immediate 8 bytes into hl
uint8_t CPU::OP_0x36() {
    uint8_t nextByte = read(++pc);
    write(hl.reg16, nextByte);
    return 3;
}

//set the carry flag to 1
uint8_t CPU::OP_0x37() {
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', true);
    return 1;
}

// If the C flag is 1, jump s8 steps from the current address stored in the pc
uint8_t CPU::OP_0x38() {
    int8_t jumpSteps = static_cast<int8_t>(read(++pc));
    // if z flag is 0
    if (readFlag('C')) {
        pc += jumpSteps;
        return 3;
    }
    // otherwise do nothing
    return 2;
}

// Add the contents of SP to the contents of register pair HL, and store the results in register pair HL.
uint8_t CPU::OP_0x39() {
    uint16_t oldHl = hl.reg16;
    hl.reg16 += sp;
    setFlag('N', false);
    setFlag('H', ((oldHl & 0x0FFF) + (sp & 0x0FFF)) > 0x0FFF);
    setFlag('C', (static_cast<uint32_t>(oldHl) + static_cast<uint32_t>(sp)) > 0xFFFF);
    return 2;
}

//read the contents of memory at the address stored in hl, and store it in a. then, decrement hl
uint8_t CPU::OP_0x3A() {
    af.a = read(hl.reg16);
    hl.reg16--;
    return 2;
}

//decrement sp by 1
uint8_t CPU::OP_0x3B() {
    sp--;
    return 2;
}

//increment contents of register a by 1
uint8_t CPU::OP_0x3C() {
    uint8_t old = af.a;
    af.a++;
    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', ((old & 0x0F) + (1 & 0x0F)) > 0x0F);
    return 1;
}

//decrement the contents of register a by 1
uint8_t CPU::OP_0x3D() {
    uint8_t old = af.a;
    af.a--;
    setFlag('Z', af.a==0);
    setFlag('N', true);
    setFlag('H', (old & 0x0F) == 0x00);
    return 1;
}

//read immediate into a
uint8_t CPU::OP_0x3E() {
    af.a = read(++pc);
    return 2;
}

//flip the carry flag
uint8_t CPU::OP_0x3F() {
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', !readFlag('C'));
    return 1;
}

// ROW x4

//Load the contents of register B into register B.
uint8_t CPU::OP_0x40() {
    bc.b = bc.b;
    return 1;
}

// Load the contents of register C into register B
uint8_t CPU::OP_0x41() {
    bc.b = bc.c;
    return 1;
}

// Load the contents of register D into register B.
uint8_t CPU::OP_0x42() {
    bc.b = de.d;
    return 1;
}

// Load the contents of register E into register B.
uint8_t CPU::OP_0x43() {
    bc.b = de.e;
    return 1;
}

// Load the contents of register H into register B.
uint8_t CPU::OP_0x44() {
    bc.b = hl.h;
    return 1;
}

// Load the contents of register L into register B.
uint8_t CPU::OP_0x45() {
    bc.b = hl.l;
    return 1;
}

//Load the 8-bit contents of memory specified by register pair HL into register B.
uint8_t CPU::OP_0x46() {
    bc.b = read(hl.reg16);
    return 2;
}

//Load the contents of register A into register B.
uint8_t CPU::OP_0x47() {
    bc.b = af.a;
    return 1;
}

//Load the contents of register B into register C.
uint8_t CPU::OP_0x48() {
    bc.c = bc.b;
    return 1;
}

//Load the contents of register C into register C.
uint8_t CPU::OP_0x49() {
    bc.c = bc.c;
    return 1;
}

// Load the contents of register D into register C.
uint8_t CPU::OP_0x4A() {
    bc.c = de.d;
    return 1;
}

//Load the contents of register E into register C
uint8_t CPU::OP_0x4B() {
    bc.c = de.e;
    return 1;
}

// Load the contents of register H into register C.
uint8_t CPU::OP_0x4C() {
    bc.c = hl.h;
    return 1;
}

//Load the contents of register L into register C.
uint8_t CPU::OP_0x4D() {
    bc.c = hl.l;
    return 1;
}

// Load the 8-bit contents of memory specified by register pair HL into register C.
uint8_t CPU::OP_0x4E() {
    bc.c = read(hl.reg16);
    return 2;
}

//Load the contents of register A into register C.
uint8_t CPU::OP_0x4F() {
    bc.c = af.a;
    return 1;
}


// ROW x5
//row 5 is super simple, just load into D (from 0-7) then load into E (from 8-F)
uint8_t CPU::OP_0x50() {
    de.d = bc.b;
    return 1;
}

uint8_t CPU::OP_0x51() {
    de.d = bc.c;
    return 1;
}

uint8_t CPU::OP_0x52() {
    de.d = de.d;
    return 1;
}

uint8_t CPU::OP_0x53() {
    de.d = de.e;
    return 1;
}

uint8_t CPU::OP_0x54() {
    de.d = hl.h;
    return 1;
}

uint8_t CPU::OP_0x55() {
    de.d = hl.l;
    return 1;
}

uint8_t CPU::OP_0x56() {
    de.d = read(hl.reg16);
    return 2;
}

uint8_t CPU::OP_0x57() {
    de.d = af.a;
    return 1;
}

uint8_t CPU::OP_0x58() {
    de.e = bc.b;
    return 1;
}

uint8_t CPU::OP_0x59() {
    de.e = bc.c;
    return 1;
}

uint8_t CPU::OP_0x5A() {
    de.e = de.d;
    return 1;
}

uint8_t CPU::OP_0x5B() {
    de.e = de.e;
    return 1;
}

uint8_t CPU::OP_0x5C() {
    de.e = hl.h;
    return 1;
}

uint8_t CPU::OP_0x5D() {
    de.e = hl.l;
    return 1;
}

uint8_t CPU::OP_0x5E() {
    de.e = read(hl.reg16);
    return 2;
}

uint8_t CPU::OP_0x5F() {
    de.e = af.a;
    return 1;
}


// ROW x6
//row 6 is also super simple loading into H and then into L
uint8_t CPU::OP_0x60() {
    hl.h = bc.b;
    return 1;
}

uint8_t CPU::OP_0x61() {
    hl.h = bc.c;
    return 1;
}

uint8_t CPU::OP_0x62() {
    hl.h = de.d;
    return 1;
}

uint8_t CPU::OP_0x63() {
    hl.h = de.e;
    return 1;
}

uint8_t CPU::OP_0x64() {
    hl.h = hl.h;
    return 1;
}

uint8_t CPU::OP_0x65() {
    hl.h = hl.l;
    return 1;
}

uint8_t CPU::OP_0x66() {
    hl.h = read(hl.reg16);
    return 2;
}

uint8_t CPU::OP_0x67() {
    hl.h = af.a;
    return 1;
}

// Load the contents of register B into register L.
uint8_t CPU::OP_0x68() {
    hl.l = bc.b;
    return 1;
}

uint8_t CPU::OP_0x69() {
    hl.l = bc.c;
    return 1;
}

uint8_t CPU::OP_0x6A() {
    hl.l = de.d;
    return 1;
}

uint8_t CPU::OP_0x6B() {
    hl.l = de.e;
    return 1;
}

uint8_t CPU::OP_0x6C() {
    hl.l = hl.h;
    return 1;
}

uint8_t CPU::OP_0x6D() {
    hl.l = hl.l;
    return 1;
}

uint8_t CPU::OP_0x6E() {
    hl.l = read(hl.reg16);
    return 2;
}

uint8_t CPU::OP_0x6F() {
    hl.l = af.a;
    return 1;
}



// ROW 7

//Store the contents of register B in the memory location specified by register pair HL.
uint8_t CPU::OP_0x70() {
    write(hl.reg16, bc.b);
    return 2;
}

//Store the contents of register C in the memory location specified by register pair HL.
uint8_t CPU::OP_0x71() {
    write(hl.reg16, bc.c);
    return 2;
}

//Store the contents of register D in the memory location specified by register pair HL.
uint8_t CPU::OP_0x72() {
    write(hl.reg16, de.d);
    return 2;
}

// Store the contents of register E in the memory location specified by register pair HL.
uint8_t CPU::OP_0x73() {
    write(hl.reg16, de.e);
    return 2;
}
// Store the contents of register H in the memory location specified by register pair HL.
uint8_t CPU::OP_0x74() {
    write(hl.reg16, hl.h);
    return 2;
}

// Store the contents of register L in the memory location specified by register pair HL.
uint8_t CPU::OP_0x75() {
    write(hl.reg16, hl.l);
    return 2;
}

// HALT INSTRUCTION
// pauses the CPU in a low-power state to save battery while keeping peripheral systems like the LCD and RAM active.
// The CPU remains frozen at the current Program Counter until it is "woken up" by a hardware interrupt or a system reset.
// Once an interrupt occurs, the CPU resumes execution, either by jumping to an interrupt handler or simply continuing to the next instruction.
uint8_t CPU::OP_0x76() {
    halted = true;
    return 1;
}

// Store the contents of register A in the memory location specified by register pair HL.
uint8_t CPU::OP_0x77() {
    write(hl.reg16, af.a);
    return 2;
}

// Load the contents of register B into register A.
uint8_t CPU::OP_0x78() {
    af.a = bc.b;
    return 1;
}

//Load the contents of register C into register A
uint8_t CPU::OP_0x79() {
    af.a = bc.c;
    return 1;
}


// Load the contents of register D into register A.
uint8_t CPU::OP_0x7A() {
    af.a = de.d;
    return 1;
}

uint8_t CPU::OP_0x7B() {
    af.a = de.e;
    return 1;
}

// Load the contents of register H into register A.
uint8_t CPU::OP_0x7C() {
    af.a = hl.h;
    return 1;
}

uint8_t CPU::OP_0x7D() {
    af.a = hl.l;
    return 1;
}

// Load the 8-bit contents of memory specified by register pair HL into register A.
uint8_t CPU::OP_0x7E() {
    af.a = read(hl.reg16);
    return 2;
}

// Load the contents of register A into register A.
uint8_t CPU::OP_0x7F() {
    af.a = af.a;
    return 1;
}

// ROW x8
// Add the contents of register B to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x80() {
    uint8_t oldA = af.a;
    af.a = af.a + bc.b;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.b & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.b)) > 0xFF);

    return 1;
}

// Add the contents of register C to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x81() {
    uint8_t oldA = af.a;
    af.a = af.a + bc.c;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.c & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.c)) > 0xFF);

    return 1;
}

//Add the contents of register D to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x82() {
    uint8_t oldA = af.a;
    af.a = af.a + de.d;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.d & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.d)) > 0xFF);

    return 1;
}

// Add the contents of register E to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x83() {
    uint8_t oldA = af.a;
    af.a = af.a + de.e;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.e & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.e)) > 0xFF);

    return 1;
}

// Add the contents of register H to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x84() {
    uint8_t oldA = af.a;
    af.a = af.a + hl.h;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.h & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.h)) > 0xFF);

    return 1;
}

// Add the contents of register L to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x85() {
    uint8_t oldA = af.a;
    af.a = af.a + hl.l;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.l & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.l)) > 0xFF);

    return 1;
}

// Add the contents of memory specified by register pair HL to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x86() {
    uint8_t val = read(hl.reg16);
    uint8_t oldA = af.a;
    af.a = af.a + val;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(val)) > 0xFF);

    return 2;
}

// Add the contents of register A to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x87() {
    uint8_t oldA = af.a;
    uint8_t val = af.a;
    af.a = af.a + val;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(val)) > 0xFF);

    return 1;
}

// Add the contents of register B and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x88() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.b) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.b & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register C and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x89() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bc.c) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bc.c & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register D and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x8A() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.d) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.d & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register E and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x8B() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(de.e) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (de.e & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register H and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x8C() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.h) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.h & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of register L and the CY flag to the contents of register A, and store the results in register A
uint8_t CPU::OP_0x8D() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(hl.l) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (hl.l & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}

// Add the contents of memory specified by register pair HL and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x8E() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t val = static_cast<uint16_t>(read(hl.reg16));
    uint16_t result = static_cast<uint16_t>(oldA) + val + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (val & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 2;
}

// Add the contents of register A and the CY flag to the contents of register A, and store the results in register A.
uint8_t CPU::OP_0x8F() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(oldA) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (oldA & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 1;
}


// ROW x9
//subtract b from a
uint8_t CPU::OP_0x90() {
    return OpcodeHelpers::SUB(af.a, bc.b, *this);
}

//subtract c from a
uint8_t CPU::OP_0x91() {
    return OpcodeHelpers::SUB(af.a, bc.c, *this);
}

//subtract d from a
uint8_t CPU::OP_0x92() {
    return OpcodeHelpers::SUB(af.a, de.d, *this);
}

//subtract e from a
uint8_t CPU::OP_0x93() {
    return OpcodeHelpers::SUB(af.a, de.e, *this);
}

//subtract h from a
uint8_t CPU::OP_0x94() {
    return OpcodeHelpers::SUB(af.a, hl.h, *this);
}

//subtract l from a
uint8_t CPU::OP_0x95() {
    return OpcodeHelpers::SUB(af.a, hl.l, *this);
}

//subtract the contents of memory at HL from a
uint8_t CPU::OP_0x96() {
    return OpcodeHelpers::SUB(af.a, read(hl.reg16), *this);
}

//subtract a from a, trivial but kept same logic
uint8_t CPU::OP_0x97() {
    return OpcodeHelpers::SUB(af.a, af.a, *this);
}

//subtract b register and carry flag from a
uint8_t CPU::OP_0x98() {
    return OpcodeHelpers::SBC(af.a, bc.b, *this);
}

//subtract c register and carry flag from a
uint8_t CPU::OP_0x99() {
    return OpcodeHelpers::SBC(af.a, bc.c, *this);
}

//subtract d register and carry flag from a
uint8_t CPU::OP_0x9A() {
    return OpcodeHelpers::SBC(af.a, de.d, *this);
}

//subtract e register and carry flag from a
uint8_t CPU::OP_0x9B() {
    return OpcodeHelpers::SBC(af.a, de.e, *this);
}

//subtract h register and carry flag from a
uint8_t CPU::OP_0x9C() {
    return OpcodeHelpers::SBC(af.a, hl.h, *this);
}

//subtract l register and carry flag from a
uint8_t CPU::OP_0x9D() {
    return OpcodeHelpers::SBC(af.a, hl.l, *this);
}

//subtract e register and carry flag from a
uint8_t CPU::OP_0x9E() {
    return OpcodeHelpers::SBC(af.a, read(hl.reg16), *this);
}

//subtract e register and carry flag from a
uint8_t CPU::OP_0x9F() {
    return OpcodeHelpers::SBC(af.a, af.a, *this);
}

// ROW xA

// Take the logical AND for each bit of the contents of register B and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA0() {
    uint8_t result = af.a & bc.b;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register C and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA1() {
    uint8_t result = af.a & bc.c;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}


// Take the logical AND for each bit of the contents of register D and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA2() {
    uint8_t result = af.a & de.d;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register E and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA3() {
    uint8_t result = af.a & de.e;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register H and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA4() {
    uint8_t result = af.a & hl.h;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of register L and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA5() {
    uint8_t result = af.a & hl.l;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical AND for each bit of the contents of memory specified by register pair HL and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA6() {
    uint8_t result = af.a & read(hl.reg16);
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 2;
}

// Take the logical AND for each bit of the contents of register A and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA7() {
    uint8_t result = af.a & af.a;
    af.a = result;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register B and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA8() {
    af.a = af.a ^ bc.b;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register C and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xA9() {
    af.a = af.a ^ bc.c;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register D and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAA() {
    af.a = af.a ^ de.d;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register E and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAB() {
    af.a = af.a ^ de.e;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register H and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAC() {
    af.a = af.a ^ hl.h;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of register L and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAD() {
    af.a = af.a ^ hl.l;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

// Take the logical exclusive-OR for each bit of the contents of memory specified by register pair HL and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAE() {
    af.a = af.a ^ read(hl.reg16);

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 2;
}

// Take the logical exclusive-OR for each bit of the contents of register A and the contents of register A, and store the results in register A.
uint8_t CPU::OP_0xAF() {
    af.a = af.a ^ af.a;

    setFlag('Z', af.a ==0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 1;
}

//ROW xB
//logical or of a and b, stored in a
uint8_t CPU::OP_0xB0() {
    return OpcodeHelpers::OR(af.a, bc.b, *this);
}

//logical or of a and c, stored in a
uint8_t CPU::OP_0xB1() {
    return OpcodeHelpers::OR(af.a, bc.c, *this);
}

//logical or of a and d, stored in a
uint8_t CPU::OP_0xB2() {
    return OpcodeHelpers::OR(af.a, de.d, *this);
}

//logical or of a and e, stored in a
uint8_t CPU::OP_0xB3() {
    return OpcodeHelpers::OR(af.a, de.e, *this);
}

//logical or of a and h, stored in a
uint8_t CPU::OP_0xB4() {
    return OpcodeHelpers::OR(af.a, hl.h, *this);
}

//logical or of a and l, stored in a
uint8_t CPU::OP_0xB5() {
    return OpcodeHelpers::OR(af.a, hl.l, *this);
}

//logical or of a and contents of memory at address in hl, stored in a
uint8_t CPU::OP_0xB6() {
    return OpcodeHelpers::OR(af.a, read(hl.reg16), *this);
}

//logical or of a and a, stored in a
uint8_t CPU::OP_0xB7() {
    return OpcodeHelpers::OR(af.a, af.a, *this);
}

//calculate a-b and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xB8() {
    return OpcodeHelpers::CP(af.a, bc.b, *this);
}

//calculate a-c and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xB9() {
    return OpcodeHelpers::CP(af.a, bc.c, *this);
}

//calculate a-d and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBA() {
    return OpcodeHelpers::CP(af.a, de.d, *this);
}

//calculate a-e and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBB() {
    return OpcodeHelpers::CP(af.a, de.e, *this);
}

//calculate a-h and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBC() {
    return OpcodeHelpers::CP(af.a, hl.h, *this);
}

//calculate a-h and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBD() {
    return OpcodeHelpers::CP(af.a, hl.l, *this);
}

//calculate a- memory at hl and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBE() {
    return OpcodeHelpers::CP(af.a, read(hl.reg16), *this);
}

//calculate a-a and set flags accordingly. same as SUB except we do not change the value of a
uint8_t CPU::OP_0xBF() {
    return OpcodeHelpers::CP(af.a, af.a, *this);
}

//ROW xC
//if zero flag is zero (meaning last op not 0) loads the contents of memory at the address in sp into
//the lower byte of pc, then increments and does the same for the higher byte
uint8_t CPU::OP_0xC0() {
    if (!readFlag('Z')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        pc--;
        return 5;
    }
    return 2;
}

//pop the contents of memory at sp into bc
uint8_t CPU::OP_0xC1() {
    bc.c = read(sp++);
    bc.b = read(sp++);
    return 3;
}

//jump to immediate 16 bit address if NZ, otherwise increment to next instruction
uint8_t CPU::OP_0xC2() {
    if (!readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//jump to immediate
uint8_t CPU::OP_0xC3() {
    uint16_t newAddress = read(++pc);
    newAddress |= (read(++pc) << 8u);
    pc = newAddress;
    pc--;
    return 4;
}

//call to immediate and push the next address to stack if NZ
uint8_t CPU::OP_0xC4() {
    if (!readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>((returnAddress & 0xFF00) >> 8u));
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//push bc onto the stack
uint8_t CPU::OP_0xC5() {
    //high byte first
    write(--sp, bc.b);
    write(--sp, bc.c);
    return 4;
}

//add the immediate 8 bit operand to the register A
uint8_t CPU::OP_0xC6() {
    uint8_t oldA = af.a;
    uint8_t bitToAdd = read(++pc);
    af.a = af.a + bitToAdd;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bitToAdd & 0x0F)) > 0x0F);
    setFlag('C', (static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bitToAdd)) > 0xFF);

    return 2;
}

//push pc onto stack, load the 0th byte of page 0 memory into the pc, RST 0
uint8_t CPU::OP_0xC7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0000;
    pc--;
    return 4;
}

//return if zero, same as c0 but with the Z flag being 1
uint8_t CPU::OP_0xC8() {
    if (readFlag('Z')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        pc--;
        return 5;
    }
    return 2;
}

//return, same as c0 but we don't care about the z flag
uint8_t CPU::OP_0xC9() {
    uint8_t lowerByte = read(sp++);
    pc = lowerByte;
    uint8_t higherByte = read(sp++);
    pc |= (higherByte << 8u);
    pc--;
    return 4;
}

//jump to immediate 16 bit address if Z, otherwise increment to next instruction
uint8_t CPU::OP_0xCA() {
    if (readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if zero flag
uint8_t CPU::OP_0xCC() {
    if (readFlag('Z')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>((returnAddress & 0xFF00) >> 8u));
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack
uint8_t CPU::OP_0xCD() {
    uint16_t newAddress = read(++pc);
    newAddress |= (read(++pc) << 8u);

    uint16_t returnAddress = ++pc;

    //write to memory the return address which is just the program counter incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((returnAddress & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

    pc = newAddress;
    pc--;
    return 6;
}

//add contents of immediate and CY flag to register A, store in register A
uint8_t CPU::OP_0xCE() {
    uint8_t cy = readFlag('C') ? 1 : 0;
    uint8_t oldA = af.a;
    uint8_t bitToAdd = read(++pc);
    uint16_t result = static_cast<uint16_t>(oldA) + static_cast<uint16_t>(bitToAdd) + cy;

    af.a = static_cast<uint8_t>(result);

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', ((oldA & 0x0F) + (bitToAdd & 0x0F) + cy) > 0x0F);
    setFlag('C', (result > 0xFF));

    return 2;
}

//push pc onto stack, load the 2nd (0x08) byte of page 0 memory into the pc, RST 1
uint8_t CPU::OP_0xCF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0008;
    pc--;
    return 4;
}



//ROW xD
//if carry flag is zero, loads the contents of memory at the address in sp into
//the lower byte of pc, then increments and does the same for the higher byte
uint8_t CPU::OP_0xD0() {
    if (!readFlag('C')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        pc--;
        return 5;
    }
    return 2;
}

//pop the contents of memory at sp into de
uint8_t CPU::OP_0xD1() {
    de.e = read(sp++);
    de.d = read(sp++);
    return 3;
}

//jump to immediate 16 bit address if NC, otherwise increment to next instruction
uint8_t CPU::OP_0xD2() {
    if (!readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if NZ
uint8_t CPU::OP_0xD4() {
    if (!readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>((returnAddress & 0xFF00) >> 8u));
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//push de onto the stack
uint8_t CPU::OP_0xD5() {
    //high byte first
    write(--sp, de.d);
    write(--sp, de.e);
    return 4;
}

//sub the immediate 8 bit operand to the register A
uint8_t CPU::OP_0xD6() {
    //we return +1 since the original function returns 1, but this is 2 cycles since we read a byte
    return OpcodeHelpers::SUB(af.a, read(++pc), *this) + 1;
}

//push pc onto stack, load the 3rd byte of page 0 memory into the pc, RST 2
uint8_t CPU::OP_0xD7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0010;
    pc--;
    return 4;
}

//return if zero, same as D0 but with the C flag being 1
uint8_t CPU::OP_0xD8() {
    if (readFlag('C')) {
        uint8_t lowerByte = read(sp++);
        pc = lowerByte;
        uint8_t higherByte = read(sp++);
        pc |= (higherByte << 8u);
        pc--;
        return 5;
    }
    return 2;
}

//returns after an interrupt. load the stack pointer into program counter, set IME to 1
uint8_t CPU::OP_0xD9() {
    IME = true;

    uint8_t lowerByte = read(sp++);
    pc = lowerByte;
    uint8_t higherByte = read(sp++);
    pc |= (higherByte << 8u);
    pc--;
    return 4;
}

//jump to immediate 16 bit address if C, otherwise increment to next instruction
uint8_t CPU::OP_0xDA() {
    if (readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);
        pc = newAddress;
        pc--;
        return 4;
    }

    pc += 2;
    return 3;
}

//call to immediate and push the next address to stack if zero flag
uint8_t CPU::OP_0xDC() {
    if (readFlag('C')) {
        uint16_t newAddress = read(++pc);
        newAddress |= (read(++pc) << 8u);

        uint16_t returnAddress = ++pc;

        //write to memory the return address which is just the program counter incremented
        //first the high byte, then the low

        write(--sp, static_cast<uint8_t>((returnAddress & 0xFF00) >> 8u));
        write(--sp, static_cast<uint8_t>(returnAddress & 0x00FF));

        pc = newAddress;
        pc--;
        return 6;
    }

    pc += 2;
    return 3;
}

//sub contents of immediate and CY flag to register A, store in register A
uint8_t CPU::OP_0xDE() {
    //we return +1 since the original function returns 1, but this is 2 cycles since we read a byte
    return OpcodeHelpers::SBC(af.a, read(++pc), *this) + 1;
}

//push pc onto stack, load the 3rd byte of page 0 memory into the pc, RST 3
uint8_t CPU::OP_0xDF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0018;
    pc--;
    return 4;
}

//ROW xE
//loads the contents of register A into the mem at the address specified by the immediate, where the immediate
//specifies the least significant byte of the memory, and FF is always the most significant byte
uint8_t CPU::OP_0xE0() {
    uint16_t newAddress = 0xFF00;
    newAddress |= read(++pc);

    write(newAddress, af.a);
    return 3;
}

//pop the contents of memory at sp into hl
uint8_t CPU::OP_0xE1() {
    hl.l = read(sp++);
    hl.h = read(sp++);
    return 3;
}

//load the contents of A into memory at address specified by 0xFF(contents of C).
uint8_t CPU::OP_0xE2() {
    uint16_t newAddress = 0xFF00;
    newAddress |= bc.c;

    write(newAddress, af.a);
    return 2;
}

//push hl onto the stack
uint8_t CPU::OP_0xE5() {
    //high byte first
    write(--sp, hl.h);
    write(--sp, hl.l);
    return 4;
}

//bitwise AND on register A and the 8 bit immediate, stored in register A
uint8_t CPU::OP_0xE6() {
    uint8_t result = af.a & read(++pc);
    af.a = result;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', true);
    setFlag('C', false);
    return 2;
}

//RST 4
uint8_t CPU::OP_0xE7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0020;
    pc--;
    return 4;
}

//add the contents of the signed 8 bit immediate to the stack pointer
//half carry determined by bit 3 -> 4,
//carry determined by bit 7 -> 8
uint8_t CPU::OP_0xE8() {
    uint16_t oldSP = sp;
    auto immediate = static_cast<int8_t>(read(++pc));
    sp = oldSP + immediate;

    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', ((oldSP & 0x000F) + (immediate & 0x000F)) > 0x000F);
    setFlag('C', ((oldSP & 0x00FF) + (immediate & 0x00FF)) > 0x00FF);

    return 4;
}

//load HL into stack pointer
uint8_t CPU::OP_0xE9() {
    pc = hl.reg16;
    pc--;
    return 1;
}

//store the contents of register A in memory at the address stored in the immediate
uint8_t CPU::OP_0xEA() {
    uint16_t address = read(++pc);
    address |= (read(++pc) << 8u);

    write(address, af.a);
    return 4;
}

//xor with the 8 bit immediate
uint8_t CPU::OP_0xEE() {
    uint8_t immediate = read(++pc);
    af.a = af.a ^ immediate;

    setFlag('Z', af.a == 0);
    setFlag('N', false);
    setFlag('H', false);
    setFlag('C', false);

    return 2;
}

//RST 5
uint8_t CPU::OP_0xEF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0028;
    pc--;
    return 4;
}

//ROW xF
//loads the contents of mem at the address specified by the immediate into register A, the immediate
//specifies the least significant byte of the memory, and FF is always the most significant byte
uint8_t CPU::OP_0xF0() {
    uint16_t newAddress = 0xFF00;
    newAddress |= read(++pc);

    af.a = read(newAddress);
    return 3;
}

//pop the contents of memory at sp into af
uint8_t CPU::OP_0xF1() {
    af.f = (read(sp++) & 0xF0);
    af.a = read(sp++);
    return 3;
}

//load memory at address in register C (0xFF(c value)) where c stores last 8 bits into register a
uint8_t CPU::OP_0xF2() {
    uint16_t newAddress = 0xFF00;
    newAddress |= bc.c;

    af.a = read(newAddress);
    return 2;
}


// IME CHANGE
//disables interrupts
uint8_t CPU::OP_0xF3() {
    IME = false;
    imeRequest =false;
    return 1;
}

//push AF onto the stack
uint8_t CPU::OP_0xF5() {
    //high byte first
    write(--sp, af.a);
    write(--sp, af.f);
    return 4;
}

//logical OR with the immediate operand and A, stored in A
uint8_t CPU::OP_0xF6() {
    return OpcodeHelpers::OR(af.a, read(++pc), *this) + 1;
}

//RST 6
uint8_t CPU::OP_0xF7() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0030;
    pc--;
    return 4;
}

//add the signed immediate to the stack pointer, store in HL
uint8_t CPU::OP_0xF8() {
    uint16_t oldSP = sp;
    auto immediate = static_cast<int8_t>(read(++pc));
    hl.reg16 = oldSP + immediate;


    setFlag('Z', false);
    setFlag('N', false);
    setFlag('H', ((oldSP & 0x000F) + (immediate & 0x000F)) > 0x000F);
    setFlag('C', ((oldSP & 0x00FF) + (immediate & 0x00FF)) > 0x00FF);

    return 3;
}

//load HL into SP
uint8_t CPU::OP_0xF9() {
    sp = hl.reg16;
    return 2;
}

//load ram at address in 16 bit immediate into register A
uint8_t CPU::OP_0xFA() {
    uint16_t address = read(++pc);
    address |= (read(++pc) << 8u);

    af.a = read(address);
    return 4;
}

// IME CHANGE
//enable interrupts
uint8_t CPU::OP_0xFB() {
    imeRequest = true; // enable the REQUEST
    return 1;
}

//compare register A with immediate. doesn't affect register A
uint8_t CPU::OP_0xFE() {
    return OpcodeHelpers::CP(af.a, read(++pc), *this) + 1;
}

//RST 6
uint8_t CPU::OP_0xFF() {
    pc++;
    //write to memory the return address which is just the pc incremented
    //first the high byte, then the low

    write(--sp, static_cast<uint8_t>((pc & 0xFF00) >> 8u));
    write(--sp, static_cast<uint8_t>(pc & 0x00FF));

    pc = 0x0038;
    pc--;
    return 4;
}

//for calling incorrect opcodes
uint8_t CPU::OP_NULL() {
    return 1;
}


// CB Functions

// Row 0x

// Rotate the contents of register B to the left.
uint8_t CPU::OP_0xCB00() {
    return OpcodeHelpers::RLC(bc.b, *this);
}

//Rotate the contents of register C to the left.
uint8_t CPU::OP_0xCB01() {
    return OpcodeHelpers::RLC(bc.c, *this);
}

//Rotate the contents of register D to the left.
uint8_t CPU::OP_0xCB02() {
    return OpcodeHelpers::RLC(de.d, *this);
}

//Rotate the contents of register E to the left.
uint8_t CPU::OP_0xCB03() {
    return OpcodeHelpers::RLC(de.e, *this);
}

// Rotate the contents of register H to the left.
uint8_t CPU::OP_0xCB04() {
    return OpcodeHelpers::RLC(hl.h, *this);
}

// Rotate the contents of register L to the left
uint8_t CPU::OP_0xCB05() {
    return OpcodeHelpers::RLC(hl.l, *this);
}

// Rotate the contents of memory specified by register pair HL to the left.
uint8_t CPU::OP_0xCB06() {
    // returns 2 + 2 (read)
    uint8_t value = read(hl.reg16);
    OpcodeHelpers::RLC(value, *this);
    write(hl.reg16, value);

    return 4;
}

// Rotate the contents of register A to the left.
uint8_t CPU::OP_0xCB07() {
    return OpcodeHelpers::RLC(af.a, *this);
}

// Rotate the contents of register B to the right.
uint8_t CPU::OP_0xCB08() {
    return OpcodeHelpers::RRC(bc.b, *this);
}

// Rotate the contents of register C to the right.
uint8_t CPU::OP_0xCB09() {
    return OpcodeHelpers::RRC(bc.c, *this);
}

// Rotate the contents of register D to the right.
uint8_t CPU::OP_0xCB0A() {
    return OpcodeHelpers::RRC(de.d, *this);
}

// Rotate the contents of register E to the right.
uint8_t CPU::OP_0xCB0B() {
    return OpcodeHelpers::RRC(de.e, *this);
}

// Rotate the contents of register H to the right.
uint8_t CPU::OP_0xCB0C() {
    return OpcodeHelpers::RRC(hl.h, *this);
}

// Rotate the contents of register L to the right.
uint8_t CPU::OP_0xCB0D() {
    return OpcodeHelpers::RRC(hl.l, *this);
}

// Rotate the contents of memory specified by register pair HL to the right.
uint8_t CPU::OP_0xCB0E() {
    uint8_t value = read(hl.reg16);
    OpcodeHelpers::RRC(value, *this);
    write(hl.reg16, value);

    return 4;
}

// Rotate the contents of register A to the right.
uint8_t CPU::OP_0xCB0F() {
    return OpcodeHelpers::RRC(af.a, *this);
}

// Row 0xCB1


// Rotate the contents of register B to the left.
uint8_t CPU::OP_0xCB10() {
    return OpcodeHelpers::RL(bc.b, *this);
}

// Rotate the contents of register C to the left.
uint8_t CPU::OP_0xCB11() {
    return OpcodeHelpers::RL(bc.c, *this);
}

// Rotate the contents of register D to the left
uint8_t CPU::OP_0xCB12() {
    return OpcodeHelpers::RL(de.d, *this);
}

// Rotate the contents of register E to the left.
uint8_t CPU::OP_0xCB13() {
    return OpcodeHelpers::RL(de.e, *this);
}

// Rotate the contents of register H to the left.
uint8_t CPU::OP_0xCB14() {
    return OpcodeHelpers::RL(hl.h, *this);
}

// Rotate the contents of register L to the left.
uint8_t CPU::OP_0xCB15() {
    return OpcodeHelpers::RL(hl.l, *this);
}

// Rotate the contents of memory specified by register pair HL to the left, through the carry flag.
uint8_t CPU::OP_0xCB16() {

    uint8_t value = read(hl.reg16);
    OpcodeHelpers::RL(value, *this);
    write(hl.reg16, value);

    return 4;
}

// Rotate the contents of register A to the left.
uint8_t CPU::OP_0xCB17() {
    return OpcodeHelpers::RL(af.a, *this);
}


uint8_t CPU::OP_0xCB18() {
    return OpcodeHelpers::RR(bc.b, *this);
}

//Rotate the contents of register C to the right.
uint8_t CPU::OP_0xCB19() {
    return OpcodeHelpers::RR(bc.c, *this);
}

// Rotate the contents of register D to the right.
uint8_t CPU::OP_0xCB1A() {
    return OpcodeHelpers::RR(de.d, *this);
}

// Rotate the contents of register E to the right.
uint8_t CPU::OP_0xCB1B() {
    return OpcodeHelpers::RR(de.e, *this);
}

// Rotate the contents of register H to the right.
uint8_t CPU::OP_0xCB1C() {
    return OpcodeHelpers::RR(hl.h, *this);
}

// Rotate the contents of register L to the right.
uint8_t CPU::OP_0xCB1D() {
    return OpcodeHelpers::RR(hl.l, *this);
}

// Rotate the contents of memory specificed by register HL to the right.
uint8_t CPU::OP_0xCB1E() {
    uint8_t value = read(hl.reg16);
    OpcodeHelpers::RR(value, *this);
    write(hl.reg16, value);

    return 4;
}

// Rotate the contents of register A to the right.
uint8_t CPU::OP_0xCB1F() {
    return OpcodeHelpers::RR(af.a, *this);
}

//ROW 0xCB2

uint8_t CPU::OP_0xCB20() {
    return OpcodeHelpers::SLA(bc.b, *this);
}

uint8_t CPU::OP_0xCB21() {
    return OpcodeHelpers::SLA(bc.c, *this);
}

uint8_t CPU::OP_0xCB22() {
    return OpcodeHelpers::SLA(de.d, *this);
}

uint8_t CPU::OP_0xCB23() {
    return OpcodeHelpers::SLA(de.e, *this);
}

uint8_t CPU::OP_0xCB24() {
    return OpcodeHelpers::SLA(hl.h, *this);
}

uint8_t CPU::OP_0xCB25() {
    return OpcodeHelpers::SLA(hl.l, *this);
}

uint8_t CPU::OP_0xCB26() {
    uint8_t byteAtAddress = read(hl.reg16);
    OpcodeHelpers::SLA(byteAtAddress, *this);
    write(hl.reg16, byteAtAddress);
    return 4;
}

uint8_t CPU::OP_0xCB27() {
    return OpcodeHelpers::SLA(af.a, *this);
}

uint8_t CPU::OP_0xCB28() {
    return OpcodeHelpers::SRA(bc.b, *this);
}

uint8_t CPU::OP_0xCB29() {
    return OpcodeHelpers::SRA(bc.c, *this);
}

uint8_t CPU::OP_0xCB2A() {
    return OpcodeHelpers::SRA(de.d, *this);
}

uint8_t CPU::OP_0xCB2B() {
    return OpcodeHelpers::SRA(de.e, *this);
}

uint8_t CPU::OP_0xCB2C() {
    return OpcodeHelpers::SRA(hl.h, *this);
}

uint8_t CPU::OP_0xCB2D() {
    return OpcodeHelpers::SRA(hl.l, *this);
}

uint8_t CPU::OP_0xCB2E() {
    uint8_t byteAtAddress = read(hl.reg16);
    OpcodeHelpers::SRA(byteAtAddress, *this);
    write(hl.reg16, byteAtAddress);
    return 4;
}

uint8_t CPU::OP_0xCB2F() {
    return OpcodeHelpers::SRA(af.a, *this);
}


// ROW 0xCB3

uint8_t CPU::OP_0xCB30() {
    return OpcodeHelpers::SWAP(bc.b, *this);
}

uint8_t CPU::OP_0xCB31() {
    return OpcodeHelpers::SWAP(bc.c, *this);
}

uint8_t CPU::OP_0xCB32() {
    return OpcodeHelpers::SWAP(de.d, *this);
}

uint8_t CPU::OP_0xCB33() {
    return OpcodeHelpers::SWAP(de.e, *this);
}

uint8_t CPU::OP_0xCB34() {
    return OpcodeHelpers::SWAP(hl.h, *this);
}

uint8_t CPU::OP_0xCB35() {
    return OpcodeHelpers::SWAP(hl.l, *this);
}

uint8_t CPU::OP_0xCB36() {
    uint8_t byteAtAddress = read(hl.reg16);
    OpcodeHelpers::SWAP(byteAtAddress, *this);
    write(hl.reg16, byteAtAddress);
    return 4;
}

uint8_t CPU::OP_0xCB37() {
    return OpcodeHelpers::SWAP(af.a, *this);
}

// Shift the contents of register B to the right.
uint8_t CPU::OP_0xCB38() {
    return OpcodeHelpers::SRL(bc.b, *this);
}

// Shift the contents of register C to the right.
uint8_t CPU::OP_0xCB39() {
    return OpcodeHelpers::SRL(bc.c, *this);
}

// etc
uint8_t CPU::OP_0xCB3A() {
    return OpcodeHelpers::SRL(de.d, *this);
}

uint8_t CPU::OP_0xCB3B() {
    return OpcodeHelpers::SRL(de.e, *this);
}

uint8_t CPU::OP_0xCB3C() {
    return OpcodeHelpers::SRL(hl.h, *this);
}

uint8_t CPU::OP_0xCB3D() {
    return OpcodeHelpers::SRL(hl.l, *this);
}

uint8_t CPU::OP_0xCB3E() {
    uint8_t byteAtAddress = read(hl.reg16);
    OpcodeHelpers::SRL(byteAtAddress, *this);
    write(hl.reg16, byteAtAddress);
    return 4;
}

uint8_t CPU::OP_0xCB3F() {
    return OpcodeHelpers::SRL(af.a, *this);
}


// ROW 0xCB4
// this sets bits in different registers or spots in memory

// Copy the complement of the contents of bit 0 in register B to the Z flag of the program
uint8_t CPU::OP_0xCB40() {
    return OpcodeHelpers::BIT(bc.b, 0, *this);
}

uint8_t CPU::OP_0xCB41() {
    return OpcodeHelpers::BIT(bc.c, 0, *this);
}

uint8_t CPU::OP_0xCB42() {
    return OpcodeHelpers::BIT(de.d, 0, *this);
}

uint8_t CPU::OP_0xCB43() {
    return OpcodeHelpers::BIT(de.e, 0, *this);
}

uint8_t CPU::OP_0xCB44() {
    return OpcodeHelpers::BIT(hl.h, 0, *this);
}

uint8_t CPU::OP_0xCB45() {
    return OpcodeHelpers::BIT(hl.l, 0, *this);
}

uint8_t CPU::OP_0xCB46() {
    return OpcodeHelpers::BIT(hl.reg16, 0, *this);
}

uint8_t CPU::OP_0xCB47() {
    return OpcodeHelpers::BIT(af.a, 0, *this);
}

uint8_t CPU::OP_0xCB48() {
    return OpcodeHelpers::BIT(bc.b, 1, *this);
}

uint8_t CPU::OP_0xCB49() {
    return OpcodeHelpers::BIT(bc.c, 1, *this);
}

uint8_t CPU::OP_0xCB4A() {
    return OpcodeHelpers::BIT(de.d, 1, *this);
}

uint8_t CPU::OP_0xCB4B() {
    return OpcodeHelpers::BIT(de.e, 1, *this);
}

uint8_t CPU::OP_0xCB4C() {
    return OpcodeHelpers::BIT(hl.h, 1, *this);
}

uint8_t CPU::OP_0xCB4D() {
    return OpcodeHelpers::BIT(hl.l, 1, *this);
}

uint8_t CPU::OP_0xCB4E() {
    return OpcodeHelpers::BIT(hl.reg16, 1, *this);
}

uint8_t CPU::OP_0xCB4F() {
    return OpcodeHelpers::BIT(af.a, 1, *this);
}

// ROW 0xCB5

uint8_t CPU::OP_0xCB50() {
    return OpcodeHelpers::BIT(bc.b, 2, *this);
}

uint8_t CPU::OP_0xCB51() {
    return OpcodeHelpers::BIT(bc.c, 2, *this);
}

uint8_t CPU::OP_0xCB52() {
    return OpcodeHelpers::BIT(de.d, 2, *this);
}

uint8_t CPU::OP_0xCB53() {
    return OpcodeHelpers::BIT(de.e, 2, *this);
}

uint8_t CPU::OP_0xCB54() {
    return OpcodeHelpers::BIT(hl.h, 2, *this);
}

uint8_t CPU::OP_0xCB55() {
    return OpcodeHelpers::BIT(hl.l, 2, *this);
}

uint8_t CPU::OP_0xCB56() {
    return OpcodeHelpers::BIT(hl.reg16, 2, *this);
}

uint8_t CPU::OP_0xCB57() {
    return OpcodeHelpers::BIT(af.a, 2, *this);
}

uint8_t CPU::OP_0xCB58() {
    return OpcodeHelpers::BIT(bc.b, 3, *this);
}

uint8_t CPU::OP_0xCB59() {
    return OpcodeHelpers::BIT(bc.c, 3, *this);
}

uint8_t CPU::OP_0xCB5A() {
    return OpcodeHelpers::BIT(de.d, 3, *this);
}

uint8_t CPU::OP_0xCB5B() {
    return OpcodeHelpers::BIT(de.e, 3, *this);
}

uint8_t CPU::OP_0xCB5C() {
    return OpcodeHelpers::BIT(hl.h, 3, *this);
}

uint8_t CPU::OP_0xCB5D() {
    return OpcodeHelpers::BIT(hl.l, 3, *this);
}

uint8_t CPU::OP_0xCB5E() {
    return OpcodeHelpers::BIT(hl.reg16, 3, *this);
}

uint8_t CPU::OP_0xCB5F() {
    return OpcodeHelpers::BIT(af.a, 3, *this);
}

// ROW 0xCB6

uint8_t CPU::OP_0xCB60() {
    return OpcodeHelpers::BIT(bc.b, 4, *this);
}

uint8_t CPU::OP_0xCB61() {
    return OpcodeHelpers::BIT(bc.c, 4, *this);
}

uint8_t CPU::OP_0xCB62() {
    return OpcodeHelpers::BIT(de.d, 4, *this);
}

uint8_t CPU::OP_0xCB63() {
    return OpcodeHelpers::BIT(de.e, 4, *this);
}

uint8_t CPU::OP_0xCB64() {
    return OpcodeHelpers::BIT(hl.h, 4, *this);
}

uint8_t CPU::OP_0xCB65() {
    return OpcodeHelpers::BIT(hl.l, 4, *this);
}

uint8_t CPU::OP_0xCB66() {
    return OpcodeHelpers::BIT(hl.reg16, 4, *this);
}

uint8_t CPU::OP_0xCB67() {
    return OpcodeHelpers::BIT(af.a, 4, *this);
}

uint8_t CPU::OP_0xCB68() {
    return OpcodeHelpers::BIT(bc.b, 5, *this);
}

uint8_t CPU::OP_0xCB69() {
    return OpcodeHelpers::BIT(bc.c, 5, *this);
}

uint8_t CPU::OP_0xCB6A() {
    return OpcodeHelpers::BIT(de.d, 5, *this);
}

uint8_t CPU::OP_0xCB6B() {
    return OpcodeHelpers::BIT(de.e, 5, *this);
}

uint8_t CPU::OP_0xCB6C() {
    return OpcodeHelpers::BIT(hl.h, 5, *this);
}

uint8_t CPU::OP_0xCB6D() {
    return OpcodeHelpers::BIT(hl.l, 5, *this);
}

uint8_t CPU::OP_0xCB6E() {
    return OpcodeHelpers::BIT(hl.reg16, 5, *this);
}

uint8_t CPU::OP_0xCB6F() {
    return OpcodeHelpers::BIT(af.a, 5, *this);
}

// ROW 0xCB7

uint8_t CPU::OP_0xCB70() {
    return OpcodeHelpers::BIT(bc.b, 6, *this);
}

uint8_t CPU::OP_0xCB71() {
    return OpcodeHelpers::BIT(bc.c, 6, *this);
}

uint8_t CPU::OP_0xCB72() {
    return OpcodeHelpers::BIT(de.d, 6, *this);
}

uint8_t CPU::OP_0xCB73() {
    return OpcodeHelpers::BIT(de.e, 6, *this);
}

uint8_t CPU::OP_0xCB74() {
    return OpcodeHelpers::BIT(hl.h, 6, *this);
}

uint8_t CPU::OP_0xCB75() {
    return OpcodeHelpers::BIT(hl.l, 6, *this);
}

uint8_t CPU::OP_0xCB76() {
    return OpcodeHelpers::BIT(hl.reg16, 6, *this);
}

uint8_t CPU::OP_0xCB77() {
    return OpcodeHelpers::BIT(af.a, 6, *this);
}

uint8_t CPU::OP_0xCB78() {
    return OpcodeHelpers::BIT(bc.b, 7, *this);
}

uint8_t CPU::OP_0xCB79() {
    return OpcodeHelpers::BIT(bc.c, 7, *this);
}

uint8_t CPU::OP_0xCB7A() {
    return OpcodeHelpers::BIT(de.d, 7, *this);
}

uint8_t CPU::OP_0xCB7B() {
    return OpcodeHelpers::BIT(de.e, 7, *this);
}

uint8_t CPU::OP_0xCB7C() {
    return OpcodeHelpers::BIT(hl.h, 7, *this);
}

uint8_t CPU::OP_0xCB7D() {
    return OpcodeHelpers::BIT(hl.l, 7, *this);
}

uint8_t CPU::OP_0xCB7E() {
    return OpcodeHelpers::BIT(hl.reg16, 7, *this);
}

uint8_t CPU::OP_0xCB7F() {
    return OpcodeHelpers::BIT(af.a, 7, *this);
}


//ROW 0xCB8
uint8_t CPU::OP_0xCB80() {
    return OpcodeHelpers::RES(bc.b, 0);
}

uint8_t CPU::OP_0xCB81() {
    return OpcodeHelpers::RES(bc.c, 0);
}

uint8_t CPU::OP_0xCB82() {
    return OpcodeHelpers::RES(de.d, 0);
}

uint8_t CPU::OP_0xCB83() {
    return OpcodeHelpers::RES(de.e, 0);
}

uint8_t CPU::OP_0xCB84() {
    return OpcodeHelpers::RES(hl.h, 0);
}

uint8_t CPU::OP_0xCB85() {
    return OpcodeHelpers::RES(hl.l, 0);
}

uint8_t CPU::OP_0xCB86() {
    return OpcodeHelpers::RES(hl.reg16, 0, *this);
}

uint8_t CPU::OP_0xCB87() {
    return OpcodeHelpers::RES(af.a, 0);
}

uint8_t CPU::OP_0xCB88() {
    return OpcodeHelpers::RES(bc.b, 1);
}

uint8_t CPU::OP_0xCB89() {
    return OpcodeHelpers::RES(bc.c, 1);
}

uint8_t CPU::OP_0xCB8A() {
    return OpcodeHelpers::RES(de.d, 1);
}

uint8_t CPU::OP_0xCB8B() {
    return OpcodeHelpers::RES(de.e, 1);
}

uint8_t CPU::OP_0xCB8C() {
    return OpcodeHelpers::RES(hl.h, 1);
}

uint8_t CPU::OP_0xCB8D() {
    return OpcodeHelpers::RES(hl.l, 1);
}

uint8_t CPU::OP_0xCB8E() {
    return OpcodeHelpers::RES(hl.reg16, 1, *this);
}

uint8_t CPU::OP_0xCB8F() {
    return OpcodeHelpers::RES(af.a, 1);
}

// ROW 0xCB9


// Reset bit 0 in register B to 0.
uint8_t CPU::OP_0xCB90() {
    return OpcodeHelpers::RES(bc.b, 2);
}

// Reset bit 0 in register C to 0.
uint8_t CPU::OP_0xCB91() {
    return OpcodeHelpers::RES(bc.c, 2);
}

// Reset bit 0 in register D to 0.
uint8_t CPU::OP_0xCB92() {
    return OpcodeHelpers::RES(de.d, 2);
}

// etc
uint8_t CPU::OP_0xCB93() {
    return OpcodeHelpers::RES(de.e, 2);
}

uint8_t CPU::OP_0xCB94() {
    return OpcodeHelpers::RES(hl.h, 2);
}

uint8_t CPU::OP_0xCB95() {
    return OpcodeHelpers::RES(hl.l, 2);
}

uint8_t CPU::OP_0xCB96() {
    return OpcodeHelpers::RES(hl.reg16, 2, *this);
}

uint8_t CPU::OP_0xCB97() {
    return OpcodeHelpers::RES(af.a, 2);
}

uint8_t CPU::OP_0xCB98() {
    return OpcodeHelpers::RES(bc.b, 3);
}

uint8_t CPU::OP_0xCB99() {
    return OpcodeHelpers::RES(bc.c, 3);
}

uint8_t CPU::OP_0xCB9A() {
    return OpcodeHelpers::RES(de.d, 3);
}

uint8_t CPU::OP_0xCB9B() {
    return OpcodeHelpers::RES(de.e, 3);
}

uint8_t CPU::OP_0xCB9C() {
    return OpcodeHelpers::RES(hl.h, 3);
}

uint8_t CPU::OP_0xCB9D() {
    return OpcodeHelpers::RES(hl.l, 3);
}

uint8_t CPU::OP_0xCB9E() {
    return OpcodeHelpers::RES(hl.reg16, 3, *this);
}

uint8_t CPU::OP_0xCB9F() {
    return OpcodeHelpers::RES(af.a, 3);
}

// ROW 0xCBA

uint8_t CPU::OP_0xCBA0() {
    return OpcodeHelpers::RES(bc.b, 4);
}

uint8_t CPU::OP_0xCBA1() {
    return OpcodeHelpers::RES(bc.c, 4);
}

uint8_t CPU::OP_0xCBA2() {
    return OpcodeHelpers::RES(de.d, 4);
}

uint8_t CPU::OP_0xCBA3() {
    return OpcodeHelpers::RES(de.e, 4);
}

uint8_t CPU::OP_0xCBA4() {
    return OpcodeHelpers::RES(hl.h, 4);
}

uint8_t CPU::OP_0xCBA5() {
    return OpcodeHelpers::RES(hl.l, 4);
}

uint8_t CPU::OP_0xCBA6() {
    return OpcodeHelpers::RES(hl.reg16, 4, *this);
}

uint8_t CPU::OP_0xCBA7() {
    return OpcodeHelpers::RES(af.a, 4);
}

uint8_t CPU::OP_0xCBA8() {
    return OpcodeHelpers::RES(bc.b, 5);
}

uint8_t CPU::OP_0xCBA9() {
    return OpcodeHelpers::RES(bc.c, 5);
}

uint8_t CPU::OP_0xCBAA() {
    return OpcodeHelpers::RES(de.d, 5);
}

uint8_t CPU::OP_0xCBAB() {
    return OpcodeHelpers::RES(de.e, 5);
}

uint8_t CPU::OP_0xCBAC() {
    return OpcodeHelpers::RES(hl.h, 5);
}

uint8_t CPU::OP_0xCBAD() {
    return OpcodeHelpers::RES(hl.l, 5);
}

uint8_t CPU::OP_0xCBAE() {
    return OpcodeHelpers::RES(hl.reg16, 5, *this);
}

uint8_t CPU::OP_0xCBAF() {
    return OpcodeHelpers::RES(af.a, 5);
}

// ROW 0xCBB

uint8_t CPU::OP_0xCBB0() {
    return OpcodeHelpers::RES(bc.b, 6);
}

uint8_t CPU::OP_0xCBB1() {
    return OpcodeHelpers::RES(bc.c, 6);
}

uint8_t CPU::OP_0xCBB2() {
    return OpcodeHelpers::RES(de.d, 6);
}

uint8_t CPU::OP_0xCBB3() {
    return OpcodeHelpers::RES(de.e, 6);
}

uint8_t CPU::OP_0xCBB4() {
    return OpcodeHelpers::RES(hl.h, 6);
}

uint8_t CPU::OP_0xCBB5() {
    return OpcodeHelpers::RES(hl.l, 6);
}

uint8_t CPU::OP_0xCBB6() {
    return OpcodeHelpers::RES(hl.reg16, 6, *this);
}

uint8_t CPU::OP_0xCBB7() {
    return OpcodeHelpers::RES(af.a, 6);
}

uint8_t CPU::OP_0xCBB8() {
    return OpcodeHelpers::RES(bc.b, 7);
}

uint8_t CPU::OP_0xCBB9() {
    return OpcodeHelpers::RES(bc.c, 7);
}

uint8_t CPU::OP_0xCBBA() {
    return OpcodeHelpers::RES(de.d, 7);
}

uint8_t CPU::OP_0xCBBB() {
    return OpcodeHelpers::RES(de.e, 7);
}

uint8_t CPU::OP_0xCBBC() {
    return OpcodeHelpers::RES(hl.h, 7);
}

uint8_t CPU::OP_0xCBBD() {
    return OpcodeHelpers::RES(hl.l, 7);
}

uint8_t CPU::OP_0xCBBE() {
    return OpcodeHelpers::RES(hl.reg16, 7, *this);
}

uint8_t CPU::OP_0xCBBF() {
    return OpcodeHelpers::RES(af.a, 7);
}

// ROW 0xCBC
//these are the set functions, also extremely repetitive just like above, but set to 1 not 0

// Set bit 0 in register B to 1.
uint8_t CPU::OP_0xCBC0() {
    return OpcodeHelpers::SET(bc.b, 0);
}

// Set bit 0 in register C to 1.
uint8_t CPU::OP_0xCBC1() {
    return OpcodeHelpers::SET(bc.c, 0);
}

// Set bit 0 in register D to 1.
uint8_t CPU::OP_0xCBC2() {
    return OpcodeHelpers::SET(de.d, 0);
}

uint8_t CPU::OP_0xCBC3() {
    return OpcodeHelpers::SET(de.e, 0);
}

uint8_t CPU::OP_0xCBC4() {
    return OpcodeHelpers::SET(hl.h, 0);
}

uint8_t CPU::OP_0xCBC5() {
    return OpcodeHelpers::SET(hl.l, 0);
}

uint8_t CPU::OP_0xCBC6() {
    return OpcodeHelpers::SET(hl.reg16, 0, *this);
}

uint8_t CPU::OP_0xCBC7() {
    return OpcodeHelpers::SET(af.a, 0);
}

uint8_t CPU::OP_0xCBC8() {
    return OpcodeHelpers::SET(bc.b, 1);
}

uint8_t CPU::OP_0xCBC9() {
    return OpcodeHelpers::SET(bc.c, 1);
}

uint8_t CPU::OP_0xCBCA() {
    return OpcodeHelpers::SET(de.d, 1);
}

uint8_t CPU::OP_0xCBCB() {
    return OpcodeHelpers::SET(de.e, 1);
}

uint8_t CPU::OP_0xCBCC() {
    return OpcodeHelpers::SET(hl.h, 1);
}

uint8_t CPU::OP_0xCBCD() {
    return OpcodeHelpers::SET(hl.l, 1);
}

uint8_t CPU::OP_0xCBCE() {
    return OpcodeHelpers::SET(hl.reg16, 1, *this);
}

uint8_t CPU::OP_0xCBCF() {
    return OpcodeHelpers::SET(af.a, 1);
}


// ROW 0xCBD — SET 2 / SET 3

uint8_t CPU::OP_0xCBD0() {
    return OpcodeHelpers::SET(bc.b, 2);
}

uint8_t CPU::OP_0xCBD1() {
    return OpcodeHelpers::SET(bc.c, 2);
}

uint8_t CPU::OP_0xCBD2() {
    return OpcodeHelpers::SET(de.d, 2);
}

uint8_t CPU::OP_0xCBD3() {
    return OpcodeHelpers::SET(de.e, 2);
}

uint8_t CPU::OP_0xCBD4() {
    return OpcodeHelpers::SET(hl.h, 2);
}

uint8_t CPU::OP_0xCBD5() {
    return OpcodeHelpers::SET(hl.l, 2);
}

uint8_t CPU::OP_0xCBD6() {
    return OpcodeHelpers::SET(hl.reg16, 2, *this);
}

uint8_t CPU::OP_0xCBD7() {
    return OpcodeHelpers::SET(af.a, 2);
}

uint8_t CPU::OP_0xCBD8() {
    return OpcodeHelpers::SET(bc.b, 3);
}

uint8_t CPU::OP_0xCBD9() {
    return OpcodeHelpers::SET(bc.c, 3);
}

uint8_t CPU::OP_0xCBDA() {
    return OpcodeHelpers::SET(de.d, 3);
}

uint8_t CPU::OP_0xCBDB() {
    return OpcodeHelpers::SET(de.e, 3);
}

uint8_t CPU::OP_0xCBDC() {
    return OpcodeHelpers::SET(hl.h, 3);
}

uint8_t CPU::OP_0xCBDD() {
    return OpcodeHelpers::SET(hl.l, 3);
}

uint8_t CPU::OP_0xCBDE() {
    return OpcodeHelpers::SET(hl.reg16, 3, *this);
}

uint8_t CPU::OP_0xCBDF() {
    return OpcodeHelpers::SET(af.a, 3);
}


// ROW 0xCBE — SET 4 / SET 5

uint8_t CPU::OP_0xCBE0() {
    return OpcodeHelpers::SET(bc.b, 4);
}

uint8_t CPU::OP_0xCBE1() {
    return OpcodeHelpers::SET(bc.c, 4);
}

uint8_t CPU::OP_0xCBE2() {
    return OpcodeHelpers::SET(de.d, 4);
}

uint8_t CPU::OP_0xCBE3() {
    return OpcodeHelpers::SET(de.e, 4);
}

uint8_t CPU::OP_0xCBE4() {
    return OpcodeHelpers::SET(hl.h, 4);
}

uint8_t CPU::OP_0xCBE5() {
    return OpcodeHelpers::SET(hl.l, 4);
}

uint8_t CPU::OP_0xCBE6() {
    return OpcodeHelpers::SET(hl.reg16, 4, *this);
}

uint8_t CPU::OP_0xCBE7() {
    return OpcodeHelpers::SET(af.a, 4);
}

uint8_t CPU::OP_0xCBE8() {
    return OpcodeHelpers::SET(bc.b, 5);
}

uint8_t CPU::OP_0xCBE9() {
    return OpcodeHelpers::SET(bc.c, 5);
}

uint8_t CPU::OP_0xCBEA() {
    return OpcodeHelpers::SET(de.d, 5);
}

uint8_t CPU::OP_0xCBEB() {
    return OpcodeHelpers::SET(de.e, 5);
}

uint8_t CPU::OP_0xCBEC() {
    return OpcodeHelpers::SET(hl.h, 5);
}

uint8_t CPU::OP_0xCBED() {
    return OpcodeHelpers::SET(hl.l, 5);
}

uint8_t CPU::OP_0xCBEE() {
    return OpcodeHelpers::SET(hl.reg16, 5, *this);
}

uint8_t CPU::OP_0xCBEF() {
    return OpcodeHelpers::SET(af.a, 5);
}


// ROW 0xCBF — SET 6 / SET 7

uint8_t CPU::OP_0xCBF0() {
    return OpcodeHelpers::SET(bc.b, 6);
}

uint8_t CPU::OP_0xCBF1() {
    return OpcodeHelpers::SET(bc.c, 6);
}

uint8_t CPU::OP_0xCBF2() {
    return OpcodeHelpers::SET(de.d, 6);
}

uint8_t CPU::OP_0xCBF3() {
    return OpcodeHelpers::SET(de.e, 6);
}

uint8_t CPU::OP_0xCBF4() {
    return OpcodeHelpers::SET(hl.h, 6);
}

uint8_t CPU::OP_0xCBF5() {
    return OpcodeHelpers::SET(hl.l, 6);
}

uint8_t CPU::OP_0xCBF6() {
    return OpcodeHelpers::SET(hl.reg16, 6, *this);
}

uint8_t CPU::OP_0xCBF7() {
    return OpcodeHelpers::SET(af.a, 6);
}

uint8_t CPU::OP_0xCBF8() {
    return OpcodeHelpers::SET(bc.b, 7);
}

uint8_t CPU::OP_0xCBF9() {
    return OpcodeHelpers::SET(bc.c, 7);
}

uint8_t CPU::OP_0xCBFA() {
    return OpcodeHelpers::SET(de.d, 7);
}

uint8_t CPU::OP_0xCBFB() {
    return OpcodeHelpers::SET(de.e, 7);
}

uint8_t CPU::OP_0xCBFC() {
    return OpcodeHelpers::SET(hl.h, 7);
}

uint8_t CPU::OP_0xCBFD() {
    return OpcodeHelpers::SET(hl.l, 7);
}

uint8_t CPU::OP_0xCBFE() {
    return OpcodeHelpers::SET(hl.reg16, 7, *this);
}

uint8_t CPU::OP_0xCBFF() {
    return OpcodeHelpers::SET(af.a, 7);
}


