#pragma once

#include<stdio.h>
#include<common.h>
#include<instructions.h>


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

    // track to halt state
    Byte halted;

    // flag registers
    struct Flag
    {
        Byte S : 1; // sign flag
        Byte Z : 1; // zero flag
        Byte AC : 1; // auxillary flag
        Byte P : 1; // parity flag
        Byte CY : 1; // carry flag

        Byte getFlagRegister()
        {
            return (S << 7) | (Z << 6) | (AC << 4) | (P << 2) | (CY);
        }

        void setFlagsFromHex(Byte flagByte)
        {
            S = (flagByte >> 7) & 0x1;   // Bit 7: Sign Flag
            Z = (flagByte >> 6) & 0x1;   // Bit 6: Zero Flag
            AC = (flagByte >> 4) & 0x1;  // Bit 4: Auxiliary Carry Flag
            P = (flagByte >> 2) & 0x1;   // Bit 2: Parity Flag
            CY = (flagByte >> 0) & 0x1;  // Bit 0: Carry Flag
        }
    } flag;

    // OUTPUTPORT structure for CPU
    struct PORT
    {
        Byte PortAddress; // output port address
        Byte Data; // value of output port
        Byte IO : 1; // weather the take INPUT = 0 or OUTPUT = 1 (a bit value)
        Byte WR : 1; // weather port is READING = 0 or WRITING = 1 (a bit value)
    } port;

    // Rest the CPU.
    void reset(Mem& memory)
    {
        B = 0, C = 0, D = 0, E = 0, H = 0, L = 0;
        W = 0, Z = 0;
        PC = 0;
        SP = 0xFFFF;
        IR = 0;
        A = 0;
        flag.S = flag.Z = flag.AC = flag.P = flag.CY = 0;
        memory.Init();
        port.Data = port.PortAddress = 0;
        port.IO = port.WR = 0;
        halted = 0;
    }

    void dumpState() const {
        printf("\ncurrent state of CPU\n");
        printf("A: 0x%x B: 0x%x C: 0x%x\n", (int)A, (int)B, (int)C);
        printf("PC: 0x%x SP: 0x%x, IR: 0x%x\n", (int)PC, (int)SP, (int)IR);
        printf("Flags: S=%d Z=%d AC=%d P=%d CY=%d\n",
            (int)flag.S, (int)flag.Z,
            (int)flag.AC, (int)flag.P, (int)flag.CY);
        printf("\n");
    }

    // Fetch the opcode from instructions.
    Byte OpCodeFetch(u32& cycles, Mem& memory )
    {
        Byte opcode = memory[PC];
        IR = opcode;
        PC++;
        cycles--;
        return opcode;
    }

    // Read a Byte (8-bit) from a memory
    Byte ReadByte(u32& cycles, Mem& memory)
    {
        Byte Data = memory[PC];
        PC++;
        cycles--;
        return Data;
    }

    // Read a Word (16-bit) from a memory
    Word ReadWord(u32& cycles, Mem& memory)
    {
        Word Data = memory[PC];
        PC++;
        Data |= (memory[PC] << 8);
        cycles-=2;
        return Data;
    }

    // Read a Byte from the specify memory Address
    Byte ReadAddress(u32& cycles, Word Address, Mem& memory)
    {
        Byte Data = memory[Address];
        cycles--;
        return Data;
    }

    // Write A Byte at the specify memory Address
    void WriteAddress(u32& cycles, Word Address, Byte value, Mem& memory)
    {
        memory[Address] = value;
        cycles--;
    }

    // Push a Byte in the Stack at an address specify by the SP (Stack Poniter) and Decrease the SP.
    void StackPUSH(u32& cycles, Byte value, Mem& memory)
    {
        SP--;
        memory[SP] = value;
        cycles--;
    }

    // POP a Byte in the Stack at an address specify by the SP (Stack Poniter) and Increase the SP.
    Byte StackPOP(u32& cycles, Mem& memory)
    {
        Byte Data = memory[SP];
        memory[SP] = 0x00;
        SP++;
        cycles--;
        return Data;
    }

    // check the even number of 1's in the given 'value'
    bool CheckOns(Byte value)
    {
        int count = 0;
        while(value)
        {
            count += (value & 0x01);
            value >>=1; //value = value >> 1
        }
        return (count % 2 == 0);
    }

    // Set Zero Flag Register ( if value is 0 , then ZERO_FLAG : 1 )
    void SetZEROFlagRegisters(Byte value)
    {
        if(value == 0)
        {
            flag.Z = 1;
        }
        else
        {
            flag.Z = 0;
        }
    }

    // Set Sign Flag Register ( NEGATIVE : 1 , POSITIVE : 0 )
    void SetSIGNFlagRegister(Byte value)
    {
        if( value & 0x80)
        {
            flag.S = 1;
        }
        else
        {
            flag.S = 0;
        }
    }

    // Set Parity Flag Register ( if no. of 1's are EVEN, then PARITY_FLAG : 1 )
    void SetPARITYFlagRegister(Byte value)
    {
        if(CheckOns(value))
        {
            flag.P = 1;
        }
        else
        {
            flag.P = 0;
        }
    }

    // Set Carry Flag Register ( if CARRY or BORROW occur, then CARRY_FLAG : 1 )
    void SetCARRYFlagRegister(Byte value, bool isAddition)
    {
        if(isAddition)
        {
            Word result = A + value + flag.CY;
            flag.CY = (result > 0xFF);
        }
        else
        {
            flag.CY = (A < value + flag.CY);
        }
    }

    void SetAUXILLAYCARRYFlagRegister(Byte firstOprand, Byte secondOprand, bool isAddition)
    {
        if(isAddition)
        {
            flag.AC = ( (firstOprand & 0x0F) + (secondOprand & 0x0F) ) > 0x0F;
        }
        else
        {
            flag.AC = ( (firstOprand & 0x0F) < (secondOprand & 0x0F) );
        }
    }

    void ANA(Byte value)
    {
        // Perform the AND operation
        A = A & value;
        SetSIGNFlagRegister(A);
        SetZEROFlagRegisters(A);
        SetAUXILLAYCARRYFlagRegister(A, value, 0);
        SetPARITYFlagRegister(A);
        SetCARRYFlagRegister(0, 0);
    }

    void nop()
    {
        // No operations
    }

    void halt()
    {
        // CPU finishes executing current instruction and halts any further execution
        halted = 1;
    }

    void execute(u32 cycles, Mem& memory)
    {
        while(cycles > 0)
        {
            Byte inst = OpCodeFetch(cycles, memory);

            switch (inst)
            {
            case INSTRUCTIONS::LDA_ADDRESS:
            {
                Word value = ReadWord(cycles, memory);
                A = ReadAddress(cycles, value, memory);
                break;
            }
            case INSTRUCTIONS::LDAX_B:
            {
                Word Address = ((B) << 8) | C;
                A = memory[Address];
                cycles--;
                break;
            }
            case INSTRUCTIONS::LDAX_D:
            {
                Word Address = ((D) << 8) | E;
                A = memory[Address];
                cycles--;
                break;
            }
            case INSTRUCTIONS::LHLD_ADDRESS:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                Byte HigherByte = ReadByte(cycles, memory);
                Word Address = ((HigherByte) << 8) | LowerByte;
                L = ReadAddress(cycles, Address, memory);
                H = ReadAddress(cycles, Address+1, memory);
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
                Byte Data = ReadByte(cycles, memory);
                A = Data;
                break;
            }
            case INSTRUCTIONS::MVI_B_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                B = Data;
                break;
            }
            case INSTRUCTIONS::MVI_C_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                C = Data;
                break;
            }
            case INSTRUCTIONS::MVI_D_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                D = Data;
                break;
            }
            case INSTRUCTIONS::MVI_E_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                E = Data;
                break;
            }
            case INSTRUCTIONS::MVI_H_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                H = Data;
                break;
            }
            case INSTRUCTIONS::MVI_L_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                L = Data;
                break;
            }
            case INSTRUCTIONS::MVI_M_DATA:
            {
                Word Address = ((H) << 8) | L;
                memory[Address] = ReadByte(cycles, memory);
                break;
            }
            case INSTRUCTIONS::LXI_B:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                C = LowerByte;
                Byte HigherByte = ReadByte(cycles, memory);
                B = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_D:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                E = LowerByte;
                Byte HigherByte = ReadByte(cycles, memory);
                D = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_H:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                L = LowerByte;
                Byte HigherByte = ReadByte(cycles, memory);
                H = HigherByte;
                break;
            }
            case INSTRUCTIONS::LXI_SP:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                Byte HigherByte = ReadByte(cycles, memory);
                SP = ((HigherByte) << 8) | LowerByte;
                break;
            }
            case INSTRUCTIONS::STA_ADDRESS:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                Byte HigherByte = ReadByte(cycles, memory);
                Word Address = ((HigherByte) << 8) | LowerByte;
                memory[Address] = A;
                cycles--;
                break;
            }
            case INSTRUCTIONS::STAX_B:
            {
                Word Address = ((B) << 8) | C;
                memory[Address] = A;
                cycles--;
                break;
            }
            case INSTRUCTIONS::STAX_D:
            {
                Word Address = ((D) << 8) | E;
                memory[Address] = A;
                cycles--;
                break;
            }
            case INSTRUCTIONS::SHLD_ADDRESS:
            {
                Byte LowerByte = ReadByte(cycles, memory);
                Byte HigherByte = ReadByte(cycles, memory);
                Word Address = ((HigherByte) << 8) | LowerByte;
                WriteAddress(cycles, Address, L, memory);
                WriteAddress(cycles, Address+1, H, memory);
                break;
            }
            case INSTRUCTIONS::XCHG:
            {
                H = H + D;
                D = H - D;  H = H - D; // exchanging H and D
                L = L + E;
                E = L - E;  L = L - E; // exchanging L and E
                break;
            }
            case INSTRUCTIONS::SPHL:
            {
                Word Address = ((H) << 8) | L;
                SP = Address;
                break;
            }
            case INSTRUCTIONS::XTHL:
            {
                H = H + memory[SP+1];
                memory[SP+1] = H - memory[SP+1];  H = H - memory[SP+1]; // exchanging H and TOP
                L = L + memory[SP];
                memory[SP] = L - memory[SP];  L = L - memory[SP]; // exchanging L and E
                break;
            }
            case INSTRUCTIONS::PCHL:
            {
                Word Address = ((H) << 8) | L;
                PC = Address;
                break;
            }
            case INSTRUCTIONS::PUSH_B:
            {
                StackPUSH(cycles, B, memory);
                StackPUSH(cycles, C, memory);
                cycles--;
                break;
            }
            case INSTRUCTIONS::PUSH_D:
            {
                StackPUSH(cycles, D, memory);
                StackPUSH(cycles, E, memory);
                cycles--;
                break;
            }
            case INSTRUCTIONS::PUSH_H:
            {
                StackPUSH(cycles, H, memory);
                StackPUSH(cycles, L, memory);
                cycles--;
                break;
            }
            case INSTRUCTIONS::PUSH_PSW:
            {
                StackPUSH(cycles, A, memory);
                StackPUSH(cycles, flag.getFlagRegister(), memory);
                cycles--;
                break;
            }
            case INSTRUCTIONS::POP_B:
            {
                C = StackPOP(cycles, memory);
                B = StackPOP(cycles, memory);
                break;
            }
            case INSTRUCTIONS::POP_D:
            {
                E = StackPOP(cycles, memory);
                D = StackPOP(cycles, memory);
                break;
            }
            case INSTRUCTIONS::POP_H:
            {
                L = StackPOP(cycles, memory);
                H = StackPOP(cycles, memory);
                break;
            }
            case INSTRUCTIONS::POP_PSW:
            {
                Byte FlagValue = StackPOP(cycles, memory);
                flag.setFlagsFromHex(FlagValue);
                A = StackPOP(cycles, memory);
                break;
            }
            case INSTRUCTIONS::OUT:
            {
                Byte Address = ReadByte(cycles, memory);
                port.PortAddress = Address;
                port.Data = A;
                port.IO = 1;
                port.WR = 1;
                cycles--;
                break;
            }
            case INSTRUCTIONS::IN:
            {
                Byte Address = ReadByte(cycles, memory);
                port.PortAddress = Address;
                A = port.Data;
                port.IO = 0;
                port.WR = 0;
                cycles--;
                break;
            }
            case INSTRUCTIONS::CMP_A:
            {
                Byte Result = A - A;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, A, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_B:
            {
                Byte Result = A - B;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, B, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_C:
            {
                Byte Result = A - C;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, C, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_D:
            {
                Byte Result = A - D;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, D, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_E:
            {
                Byte Result = A - E;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, E, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_H:
            {
                Byte Result = A - H;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, H, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_L:
            {
                Byte Result = A - L;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, L, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CMP_M:
            {
                Word Address = ((H) << 8) | L;
                Byte Data = memory[Address];
                Byte Result = A - Data;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, Data, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::CPI_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                Byte Result = A - Data;
                SetSIGNFlagRegister(Result);
                SetZEROFlagRegisters(Result);
                SetAUXILLAYCARRYFlagRegister(A, Data, 0);
                SetPARITYFlagRegister(Result);
                SetCARRYFlagRegister(Result, 0);
                break;
            }
            case INSTRUCTIONS::ANA_A:
            {
                ANA(A);
                break;
            }
            case INSTRUCTIONS::ANA_B:
            {
                ANA(B);
                break;
            }
            case INSTRUCTIONS::ANA_C:
            {
                ANA(C);
                break;
            }
            case INSTRUCTIONS::ANA_D:
            {
                ANA(D);
                break;
            }
            case INSTRUCTIONS::ANA_E:
            {
                ANA(E);
                break;
            }
            case INSTRUCTIONS::ANA_H:
            {
                ANA(H);
                break;
            }
            case INSTRUCTIONS::ANA_L:
            {
                ANA(L);
                break;
            }
            case INSTRUCTIONS::DCR_A:
            {
                Byte oldValue = A;
                A--;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                break;
            }
            case INSTRUCTIONS::DCR_B:
            {
                Byte oldValue = B;
                B--;
                SetSIGNFlagRegister(B);
                SetZEROFlagRegisters(B);
                SetAUXILLAYCARRYFlagRegister(B, oldValue, 0);
                SetPARITYFlagRegister(B);
                break;
            }
            case INSTRUCTIONS::DCR_C:
            {
                Byte oldValue = C;
                C--;
                SetSIGNFlagRegister(C);
                SetZEROFlagRegisters(C);
                SetAUXILLAYCARRYFlagRegister(C, oldValue, 0);
                SetPARITYFlagRegister(C);
                break;
            }
            case INSTRUCTIONS::DCR_D:
            {
                Byte oldValue = D;
                D--;
                SetSIGNFlagRegister(D);
                SetZEROFlagRegisters(D);
                SetAUXILLAYCARRYFlagRegister(D, oldValue, 0);
                SetPARITYFlagRegister(D);
                break;
            }
            case INSTRUCTIONS::DCR_E:
            {
                Byte oldValue = E;
                E--;
                SetSIGNFlagRegister(E);
                SetZEROFlagRegisters(E);
                SetAUXILLAYCARRYFlagRegister(E, oldValue, 0);
                SetPARITYFlagRegister(E);
                break;
            }
            case INSTRUCTIONS::DCR_H:
            {
                Byte oldValue = H;
                H--;
                SetSIGNFlagRegister(H);
                SetZEROFlagRegisters(H);
                SetAUXILLAYCARRYFlagRegister(H, oldValue, 0);
                SetPARITYFlagRegister(H);
                break;
            }
            case INSTRUCTIONS::DCR_L:
            {
                Byte oldValue = L;
                L--;
                SetSIGNFlagRegister(L);
                SetZEROFlagRegisters(L);
                SetAUXILLAYCARRYFlagRegister(L, oldValue, 0);
                SetPARITYFlagRegister(L);
                break;
            }
            case INSTRUCTIONS::DCR_M:
            {
                Word Address = ((H) << 8) | L;
                Byte oldValue = memory[Address];
                cycles--;
                memory[Address] = memory[Address] - 1;
                cycles--;
                SetSIGNFlagRegister(memory[Address]);
                SetZEROFlagRegisters(memory[Address]);
                SetAUXILLAYCARRYFlagRegister( memory[Address], oldValue, 0);
                SetPARITYFlagRegister(memory[Address]);
                break;
            }
            case INSTRUCTIONS::DCX_B:
            {
                Word Address = ((B) << 8) | C;
                memory[Address] = memory[Address] - 1;
                break;
            }
            case INSTRUCTIONS::DCX_D:
            {
                Word Address = ((D) << 8) | E;
                memory[Address] = memory[Address] - 1;
                break;
            }
            case INSTRUCTIONS::DCX_H:
            {
                Word Address = ((H) << 8) | L;
                memory[Address] = memory[Address] - 1;
                break;
            }
            case INSTRUCTIONS::DCX_SP:
            {
                memory[SP] = memory[SP] - 1;
                break;
            }
            case INSTRUCTIONS::INR_A:
            {
                Byte oldValue = A;
                A++;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 1);
                SetPARITYFlagRegister(A);
                break;
            }
            case INSTRUCTIONS::INR_B:
            {
                Byte oldValue = B;
                B++;
                SetSIGNFlagRegister(B);
                SetZEROFlagRegisters(B);
                SetAUXILLAYCARRYFlagRegister(B, oldValue, 1);
                SetPARITYFlagRegister(B);
                break;
            }
            case INSTRUCTIONS::INR_C:
            {
                Byte oldValue = C;
                C++;
                SetSIGNFlagRegister(C);
                SetZEROFlagRegisters(C);
                SetAUXILLAYCARRYFlagRegister(C, oldValue, 1);
                SetPARITYFlagRegister(C);
                break;
            }
            case INSTRUCTIONS::INR_D:
            {
                Byte oldValue = D;
                D++;
                SetSIGNFlagRegister(D);
                SetZEROFlagRegisters(D);
                SetAUXILLAYCARRYFlagRegister(D, oldValue, 1);
                SetPARITYFlagRegister(D);
                break;
            }
            case INSTRUCTIONS::INR_E:
            {
                Byte oldValue = E;
                E++;
                SetSIGNFlagRegister(E);
                SetZEROFlagRegisters(E);
                SetAUXILLAYCARRYFlagRegister(E, oldValue, 1);
                SetPARITYFlagRegister(E);
                break;
            }
            case INSTRUCTIONS::INR_H:
            {
                Byte oldValue = H;
                H++;
                SetSIGNFlagRegister(H);
                SetZEROFlagRegisters(H);
                SetAUXILLAYCARRYFlagRegister(H, oldValue, 1);
                SetPARITYFlagRegister(H);
                break;
            }
            case INSTRUCTIONS::INR_L:
            {
                Byte oldValue = L;
                L++;
                SetSIGNFlagRegister(L);
                SetZEROFlagRegisters(L);
                SetAUXILLAYCARRYFlagRegister(L, oldValue, 1);
                SetPARITYFlagRegister(L);
                break;
            }
            case INSTRUCTIONS::INX_B:
            {
                Word Address = ((B) << 8) | C;
                memory[Address] = memory[Address] + 1;
                break;
            }
            case INSTRUCTIONS::INX_D:
            {
                Word Address = ((D) << 8) | E;
                memory[Address] = memory[Address] + 1;
                break;
            }
            case INSTRUCTIONS::INX_H:
            {
                Word Address = ((H) << 8) | L;
                memory[Address] = memory[Address] + 1;
                break;
            }
            case INSTRUCTIONS::INX_SP:
            {
                memory[SP] = memory[SP] + 1;
                break;
            }
            case INSTRUCTIONS::ADD_A:
            {
                Byte oldValue = A;
                A = A + A;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_B:
            {
                Byte oldValue = A;
                A = A + B;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_C:
            {
                Byte oldValue = A;
                A = A + C;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_D:
            {
                Byte oldValue = A;
                A = A + D;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_E:
            {
                Byte oldValue = A;
                A = A + E;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_H:
            {
                Byte oldValue = A;
                A = A + H;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_L:
            {
                Byte oldValue = A;
                A = A + L;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADD_M:
            {
                Word Address = ((H) << 8) | L;
                Byte oldValue = memory[Address];
                A = A + memory[Address];
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADI_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                Byte oldValue = A;
                A = A + Data;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_A:
            {
                Byte oldValue = A;
                A = A + A + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_B:
            {
                Byte oldValue = A;
                A = A + B + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_C:
            {
                Byte oldValue = A;
                A = A + C + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_D:
            {
                Byte oldValue = A;
                A = A + D + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_E:
            {
                Byte oldValue = A;
                A = A + E + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_H:
            {
                Byte oldValue = A;
                A = A + H + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_L:
            {
                Byte oldValue = A;
                A = A + L + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::ADC_M:
            {
                Byte oldValue = A;
                Word Address = ((H) << 8) | L;
                Byte Data = ReadAddress(cycles, Address, memory);
                A = A + Data + flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(A, oldValue, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(oldValue, 0);
                break;
            }
            case INSTRUCTIONS::SUB_A:
            {
                Byte oldValue = A;
                A = A - A;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_B:
            {
                Byte oldValue = A;
                A = A - B;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_C:
            {
                Byte oldValue = A;
                A = A - C;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_D:
            {
                Byte oldValue = A;
                A = A - D;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_E:
            {
                Byte oldValue = A;
                A = A - E;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_H:
            {
                Byte oldValue = A;
                A = A - H;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_L:
            {
                Byte oldValue = A;
                A = A - L;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUB_M:
            {
                Word Address = ((H) << 8) | L;
                Byte oldValue = memory[Address];
                A = A - memory[Address];
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SUI_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                Byte oldValue = A;
                A = A - Data;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_A:
            {
                Byte oldValue = A;
                A = A - A - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_B:
            {
                Byte oldValue = A;
                A = A - B - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_C:
            {
                Byte oldValue = A;
                A = A - C - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_D:
            {
                Byte oldValue = A;
                A = A - D - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_E:
            {
                Byte oldValue = A;
                A = A - E - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_H:
            {
                Byte oldValue = A;
                A = A - H - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_L:
            {
                Byte oldValue = A;
                A = A - L - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBB_M:
            {
                Byte oldValue = A;
                Word Address = ((H) << 8) | L;
                Byte Data = ReadAddress(cycles, Address, memory);
                A = A - Data - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::SBI_DATA:
            {
                Byte Data = ReadByte(cycles, memory);
                Byte oldValue = A;
                A = A - Data - flag.CY;
                SetSIGNFlagRegister(A);
                SetZEROFlagRegisters(A);
                SetAUXILLAYCARRYFlagRegister(oldValue, A, 0);
                SetPARITYFlagRegister(A);
                SetCARRYFlagRegister(A, 0);
                break;
            }
            case INSTRUCTIONS::NOP:
            {
                nop();
                break;
            }
            case INSTRUCTIONS::HLT:
            {
                halt();
                cycles = 0;
                break;
            }
            default:
            {
                printf("Instruction not handled %d", inst);
                break;
            }
            }
        }
    }
};
