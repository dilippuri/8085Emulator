#pragma once

#include<common.h>

// 8085 Instruction set
struct INSTRUCTIONS
{
// DATA TRANSFER INSTRUCTIONS

    //MOV Instructions
    static Byte constexpr MOV_A_B = 0x78;
    static Byte constexpr MOV_A_C = 0x79;
    static Byte constexpr MOV_A_D = 0x7A;
    static Byte constexpr MOV_A_E = 0x7B;
    static Byte constexpr MOV_A_H = 0x7C;
    static Byte constexpr MOV_A_L = 0x7D;
    static Byte constexpr MOV_A_M = 0x7E;
    static Byte constexpr MOV_A_A = 0x7F;

    static Byte constexpr MOV_B_A = 0x47;
    static Byte constexpr MOV_B_B = 0x40;
    static Byte constexpr MOV_B_C = 0x41;
    static Byte constexpr MOV_B_D = 0x42;
    static Byte constexpr MOV_B_E = 0x43;
    static Byte constexpr MOV_B_H = 0x44;
    static Byte constexpr MOV_B_L = 0x45;
    static Byte constexpr MOV_B_M = 0x46;
    
    static Byte constexpr MOV_C_A = 0x4F;
    static Byte constexpr MOV_C_B = 0x48;
    static Byte constexpr MOV_C_C = 0x49;
    static Byte constexpr MOV_C_D = 0x4A;
    static Byte constexpr MOV_C_E = 0x4B;
    static Byte constexpr MOV_C_H = 0x4C;
    static Byte constexpr MOV_C_L = 0x4D;
    static Byte constexpr MOV_C_M = 0x4E;

    static Byte constexpr MOV_D_A = 0x57;
    static Byte constexpr MOV_D_B = 0x50;
    static Byte constexpr MOV_D_C = 0x51;
    static Byte constexpr MOV_D_D = 0x52;
    static Byte constexpr MOV_D_E = 0x53;
    static Byte constexpr MOV_D_H = 0x54;
    static Byte constexpr MOV_D_L = 0x55;
    static Byte constexpr MOV_D_M = 0x56;

    static Byte constexpr MOV_E_A = 0x5F;
    static Byte constexpr MOV_E_B = 0x58;
    static Byte constexpr MOV_E_C = 0x59;
    static Byte constexpr MOV_E_D = 0x5A;
    static Byte constexpr MOV_E_E = 0x5B;
    static Byte constexpr MOV_E_H = 0x5C;
    static Byte constexpr MOV_E_L = 0x5D;
    static Byte constexpr MOV_E_M = 0x5E;

    static Byte constexpr MOV_H_A = 0x67;
    static Byte constexpr MOV_H_B = 0x60;
    static Byte constexpr MOV_H_C = 0x61;
    static Byte constexpr MOV_H_D = 0x62;
    static Byte constexpr MOV_H_E = 0x63;
    static Byte constexpr MOV_H_H = 0x64;
    static Byte constexpr MOV_H_L = 0x65;
    static Byte constexpr MOV_H_M = 0x66;

    static Byte constexpr MOV_L_A = 0x6F;
    static Byte constexpr MOV_L_B = 0x68;
    static Byte constexpr MOV_L_C = 0x69;
    static Byte constexpr MOV_L_D = 0x6A;
    static Byte constexpr MOV_L_E = 0x6B;
    static Byte constexpr MOV_L_H = 0x6C;
    static Byte constexpr MOV_L_L = 0x6D;
    static Byte constexpr MOV_L_M = 0x6E;

    static Byte constexpr MOV_M_A = 0x77;
    static Byte constexpr MOV_M_B = 0x70;
    static Byte constexpr MOV_M_C = 0x71;
    static Byte constexpr MOV_M_D = 0x72;
    static Byte constexpr MOV_M_E = 0x73;
    static Byte constexpr MOV_M_H = 0x74;
    static Byte constexpr MOV_M_L = 0x75;

    //MVI Instructions
    static Byte constexpr MVI_A_DATA = 0x3E;
    static Byte constexpr MVI_B_DATA = 0x06;
    static Byte constexpr MVI_C_DATA = 0x0E;
    static Byte constexpr MVI_D_DATA = 0x16;
    static Byte constexpr MVI_E_DATA = 0x1E;
    static Byte constexpr MVI_H_DATA = 0x26;
    static Byte constexpr MVI_L_DATA = 0x2E;
    static Byte constexpr MVI_M_DATA = 0x36;

    //LXI (Load Register Pair Immediate) Instructions
    static Byte constexpr LXI_B = 0x01;
    static Byte constexpr LXI_D = 0x11;
    static Byte constexpr LXI_H = 0x21;
    static Byte constexpr LXI_SP = 0x31;

    static Byte constexpr LDA_ADDRESS = 0x3A; //Load Accumulator Direct
    
    static Byte constexpr LDAX_B = 0x0A; // Load Data of Address pointing by the BC register in Accumulator
    static Byte constexpr LDAX_D = 0x1A; // Load Data of Address pointing by the DE register in Accumulator

    static Byte constexpr LHLD_ADDRESS = 0x2A; 

    // STA Instruction
    static Byte constexpr STA_ADDRESS = 0x32;

    static Byte constexpr STAX_B = 0x02;
    static Byte constexpr STAX_D = 0x12;

    static Byte constexpr SHLD_ADDRESS = 0x22;

    // Exchange HL and DE register data into eachother
    static Byte constexpr XCHG = 0xEB;

    // Load HL into Stack Pointer
    static Byte constexpr SPHL = 0xF9;

    // Exchange HL with the TOP of Stack
    static Byte constexpr XTHL = 0xE3;

    // load HL into PC
    static Byte constexpr PCHL = 0xE9;

    // PUSH Instructions
    static Byte constexpr PUSH_B = 0xC5;
    static Byte constexpr PUSH_D = 0xD5;
    static Byte constexpr PUSH_H = 0xE5;
    static Byte constexpr PUSH_PSW = 0xF5;

    // POP Instructions
    static Byte constexpr POP_B = 0xC1;
    static Byte constexpr POP_D = 0xD1;
    static Byte constexpr POP_H = 0xE1;
    static Byte constexpr POP_PSW = 0xF1;

    // OUT Instruction
    static Byte constexpr OUT = 0xD3;

    // IN Instruction
    static Byte constexpr IN = 0xDB;


// LOGICAL INSTRUCTIONS
   
    // CMP Instruction
    static Byte constexpr CMP_A = 0xBF;
    static Byte constexpr CMP_B = 0xB8;
    static Byte constexpr CMP_C = 0xB9;
    static Byte constexpr CMP_D = 0xBA;
    static Byte constexpr CMP_E = 0xBB;
    static Byte constexpr CMP_H = 0xBC;
    static Byte constexpr CMP_L = 0xBD;
    static Byte constexpr CMP_M = 0xBE; // Compare with memory location pointing by the HL register pair

    static Byte constexpr CPI_DATA = 0xFE;

    // AND Instruction
    static Byte constexpr ANA_A = 0xA7;
    static Byte constexpr ANA_B = 0xA0;
    static Byte constexpr ANA_C = 0xA1;
    static Byte constexpr ANA_D = 0xA2;
    static Byte constexpr ANA_E = 0xA3;
    static Byte constexpr ANA_H = 0xA4;
    static Byte constexpr ANA_L = 0xA5;
    static Byte constexpr ANA_M = 0xA6; // AND with memory location pointing by the HL register pair

    static Byte constexpr DCR_A = 0x3D;
    static Byte constexpr DCR_B = 0x05;
    static Byte constexpr DCR_C = 0x0D;
    static Byte constexpr DCR_D = 0x15;
    static Byte constexpr DCR_E = 0x1D;
    static Byte constexpr DCR_H = 0x25;
    static Byte constexpr DCR_L = 0x2D;
    static Byte constexpr DCR_M = 0x35;

    static Byte constexpr DCX_B = 0x0B;
    static Byte constexpr DCX_D = 0x1B;
    static Byte constexpr DCX_H = 0x2B;
    static Byte constexpr DCX_SP = 0x3B;

    static Byte constexpr INR_A = 0x3C;
    static Byte constexpr INR_B = 0x04;
    static Byte constexpr INR_C = 0x0C;
    static Byte constexpr INR_D = 0x14;
    static Byte constexpr INR_E = 0x1C;
    static Byte constexpr INR_H = 0x24;
    static Byte constexpr INR_L = 0x2C;
    static Byte constexpr INR_M = 0x34;

    static Byte constexpr INX_B = 0x03;
    static Byte constexpr INX_D = 0x13;
    static Byte constexpr INX_H = 0x23;
    static Byte constexpr INX_SP = 0x33;


};