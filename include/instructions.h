using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;


struct INSTRUCTIONS
{
    static Byte constexpr LDA = 0x3A; //Load Accumulator Direct
    
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
};