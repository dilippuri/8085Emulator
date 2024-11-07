#include <stdio.h>
#include"instructions.h"

using Byte = unsigned char; // 8-bit memory
using Word = unsigned short; // 16-bit memory
using u32 = unsigned int; // 32-bit memory

//64KB memory structure
struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    // initalize all bytes to 0x0000
    void Init()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0;
        }
        
    }

    Byte operator[](u32 Address) const
    {
        return Data[Address];
    }

    Byte& operator[](u32 Address)
    {
        return Data[Address];
    }

};

//8085 CPU structure
struct CPU
{
    // general purpose registers
    Byte B, C, D, E, H, L;

    Byte W, Z; // temprory register

    Word PC; // program counter
    Word SP; // stack pointer
    Word IR; // instruction register

    // special purpose register
    Byte A; // accumulator

    // flag registers
    struct Flag
    {
        Byte S : 1; // sign flag
        Byte Z : 1; // zero flag
        Byte AC : 1; // auxillary flag
        Byte P : 1; // parity flag
        Byte CY : 1; // carry flag
    } flag;
    
    
    void Reset( Mem& memory)
    {
        B, C, D, E, H, L = 0;
        W, Z = 0;
        PC = 0;
        SP = 0xFFFF;
        A = 0;
        flag.S = flag.Z = flag.AC = flag.P = flag.CY = 0;
        memory.Init();
    }

    Byte OpCodeFetch(u32& Cycles, Mem& memory )
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    Byte ReadByte(u32& Cycles, Mem& memory)
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    Word ReadWord(u32& Cycles, Mem& memory)
    {
        Word Data = memory[PC];
        PC++;
        Data |= (memory[PC] << 8);
        Cycles-=2;
        return Data;
    }

    Byte ReadAddress(u32& Cycles, Word Address, Mem& memory)
    {
        Byte Data = memory[Address];
        Cycles--;
        return Data;
    }


    
    void Execute(u32 Cycles, Mem& memory)
    {
        while(Cycles > 0)
        {
            Byte Ins = OpCodeFetch(Cycles, memory);

            switch (Ins)
            {
            case INSTRUCTIONS::LDA:
            {
                Word value = ReadWord(Cycles, memory);
                A = ReadAddress(Cycles, value, memory);
                break;
            }
            case INSTRUCTIONS::LDAX_B:
            {
                Word Address = ((B) << 8) | C;
                A = memory[Address];
                Cycles--;
                break;
            }
            case INSTRUCTIONS::LDAX_D:
            {
                Word Address = ((D) << 8) | E;
                A = memory[Address];
                Cycles--;
                break;
            }
            case INSTRUCTIONS::MOV_A_A:
            {
                A = A;
                break;
            }
            case INSTRUCTIONS::MOV_A_B:
            {
                A = B;
                break;
            }
            case INSTRUCTIONS::MOV_A_C:
            {
                A = C;
                break;
            }
            case INSTRUCTIONS::MOV_A_D:
            {
                A = D;
                break;
            }
            case INSTRUCTIONS::MOV_A_E:
            {
                A = E;
                break;
            }
            case INSTRUCTIONS::MOV_A_H:
            {
                A = H;
                break;
            }
            case INSTRUCTIONS::MOV_A_L:
            {
                A = L;
                break;
            }
            
            case INSTRUCTIONS::MOV_B_C:
            {
                B = C;
                break;
            }
            case INSTRUCTIONS::MOV_H_L:
            {
                H = L;
                break;
            }
            case INSTRUCTIONS::MOV_M_A:
            {
                Word Address = ((H) << 8) | L;
                memory[Address] = A;
                break;
            }
            case INSTRUCTIONS::MOV_A_M:
            {
                Word Address = ((H) << 8) | L;
                A = memory[Address];
                break;
            }
            case INSTRUCTIONS::MVI_A_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                A = Data;
                break;
            }
            case INSTRUCTIONS::MVI_B_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                B = Data;
                break;
            }
            case INSTRUCTIONS::MVI_C_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                C = Data;
                break;
            }
            case INSTRUCTIONS::MVI_D_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                D = Data;
                break;
            }
            case INSTRUCTIONS::MVI_E_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                E = Data;
                break;
            }
            case INSTRUCTIONS::MVI_H_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                H = Data;
                break;
            }
            case INSTRUCTIONS::MVI_L_DATA:
            {
                Byte Data = ReadByte(Cycles, memory);
                L = Data;
                break;
            }
            case INSTRUCTIONS::MVI_M_DATA:
            {
                Word Address = ((H) << 8) | L;
                memory[Address] = ReadByte(Cycles, memory);
                break;
            }
            case INSTRUCTIONS::LXI_B:
            {
                Byte LowerByte = ReadByte(Cycles, memory);
                C = LowerByte;
                Byte HigherByte = ReadByte(Cycles, memory);
                B = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_D:
            {
                Byte LowerByte = ReadByte(Cycles, memory);
                E = LowerByte;
                Byte HigherByte = ReadByte(Cycles, memory);
                D = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_H:
            {
                Byte LowerByte = ReadByte(Cycles, memory);
                L = LowerByte;
                Byte HigherByte = ReadByte(Cycles, memory);
                H = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_SP:
            {
                Byte LowerByte = ReadByte(Cycles, memory);
                Byte HigherByte = ReadByte(Cycles, memory);
                SP = ((HigherByte) << 8) | LowerByte;
                break;
            }
            case INSTRUCTIONS::STA_ADDRESS:
            {
                Byte LowerByte = ReadByte(Cycles, memory);
                Byte HigherByte = ReadByte(Cycles, memory);
                Word Address = ((HigherByte) << 8) | LowerByte;
                memory[Address] = A;
                Cycles--;
                break;
            }
            case INSTRUCTIONS::STAX_B:
            {
                Word Address = ((B) << 8) | C;
                memory[Address] = A;
                Cycles--;
                break;
            }
            case INSTRUCTIONS::STAX_D:
            {
                Word Address = ((D) << 8) | E;
                memory[Address] = A;
                Cycles--;
                break;
            }
            default:
            {
                printf("Instruction not handled %d", Ins);
                break;
            }
            }
        }
    }

};