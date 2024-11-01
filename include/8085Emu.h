#include <stdio.h>
#include"instructions.h"

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

//this CPU use 64KB of memory
struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    // initalizing bytes to 0x0000
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
                Word Address = ((1 & H) << 8) | L;
                memory[Address] = A;
                break;
            }
            case INSTRUCTIONS::MOV_A_M:
            {
                Word Address = ((1 & H) << 8) | L;
                A = memory[Address];
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