#include <gtest/gtest.h>
#include <8085Emu.h>

// Sample test fixture for setting up Emulator instance
class EmulatorTest : public ::testing::Test {
protected:
    Mem mem;
    CPU cpu;

    void SetUp() override {
        // Initialize emulator state if needed
        cpu.Reset(mem);
    }

    void TearDown() override {
        // Clean up emulator state if needed
    }
};

TEST_F(EmulatorTest, LDA_ADDRESS) {
    cpu.Reset(mem);
    mem[0x000A] = 0x0F;
    mem[0x0000] = INSTRUCTIONS::LDA_ADDRESS;
    mem[0x0001] = 0x0A;
    mem[0x0002] = 0x00;
    cpu.Execute(4, mem);
    EXPECT_EQ(cpu.A, 0x0F);
}

TEST_F(EmulatorTest, MOV_A_A) {
    cpu.Reset(mem);
    cpu.A = 0xFF;
    Byte valueOfA = cpu.A;
    mem[0x0000] = INSTRUCTIONS::MOV_A_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, valueOfA);
}

TEST_F(EmulatorTest, MOV_A_B) {
    cpu.Reset(mem);
    cpu.B = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.B);
}

TEST_F(EmulatorTest, MOV_A_C) {
    cpu.Reset(mem);
    cpu.C = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.C);
}

TEST_F(EmulatorTest, MOV_A_D) {
    cpu.Reset(mem);
    cpu.D = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.D);
}

TEST_F(EmulatorTest, MOV_A_E) {
    cpu.Reset(mem);
    cpu.E = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.E);
}

TEST_F(EmulatorTest, MOV_A_H) {
    cpu.Reset(mem);
    cpu.H = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.H);
}

TEST_F(EmulatorTest, MOV_A_L) {
    cpu.Reset(mem);
    cpu.L = 0xFF;
    mem[0x0000] = INSTRUCTIONS::MOV_A_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, cpu.L);
}

TEST_F(EmulatorTest, MOV_M_A) {
    cpu.Reset(mem);
    cpu.H = 0x00;
    cpu.L = 0x0A;
    cpu.A = 0x0F;
    mem[0x0000] = INSTRUCTIONS::MOV_M_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x000A], 0x0F);
}

TEST_F(EmulatorTest, MOV_A_M) {
    cpu.Reset(mem);
    cpu.H = 0x00;
    cpu.L = 0x0A;
    mem[0x000A] = 0x0F;
    mem[0x0000] = INSTRUCTIONS::MOV_A_M;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, 0x0F);
}

TEST_F(EmulatorTest, MVI_A_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_A_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.A, 0x0E);
}

TEST_F(EmulatorTest, MVI_B_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_B_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.B, 0x0E);
}

TEST_F(EmulatorTest, MVI_C_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_C_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.C, 0x0E);
}

TEST_F(EmulatorTest, MVI_D_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_D_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.D, 0x0E);
}

TEST_F(EmulatorTest, MVI_E_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_E_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.E, 0x0E);
}

TEST_F(EmulatorTest, MVI_H_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_H_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.H, 0x0E);
}

TEST_F(EmulatorTest, MVI_L_DATA) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_L_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.L, 0x0E);
}

TEST_F(EmulatorTest, MVI_M_DATA) {
    cpu.Reset(mem);
    cpu.H = 0x00;
    cpu.L = 0x0A;
    mem[0x000A] = 0x0F;
    mem[0x0000] = INSTRUCTIONS::MVI_M_DATA;
    mem[0x0001] = 0x0E;
    cpu.Execute(2, mem);
    EXPECT_EQ(mem[0x000A], 0x0E);
}

TEST_F(EmulatorTest, LXI_B) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::LXI_B;
    mem[0x0001] = 0x32;
    mem[0x0002] = 0x20;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.B, 0x20);
    EXPECT_EQ(cpu.C, 0x32);
}

TEST_F(EmulatorTest, LXI_D) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::LXI_D;
    mem[0x0001] = 0x32;
    mem[0x0002] = 0x20;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.D, 0x20);
    EXPECT_EQ(cpu.E, 0x32);
}

TEST_F(EmulatorTest, LXI_H) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::LXI_H;
    mem[0x0001] = 0x32;
    mem[0x0002] = 0x20;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.H, 0x20);
    EXPECT_EQ(cpu.L, 0x32);
}

TEST_F(EmulatorTest, LXI_SP) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::LXI_SP;
    mem[0x0001] = 0x32;
    mem[0x0002] = 0x20;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.SP, 0x2032);
}

TEST_F(EmulatorTest, STA_ADDRESS) {
    cpu.Reset(mem);
    cpu.A = 0x0F;
    mem[0x0000] = INSTRUCTIONS::STA_ADDRESS;
    mem[0x0001] = 0x0A;
    mem[0x0002] = 0x20;
    cpu.Execute(4, mem);
    EXPECT_EQ(mem[0x200A], 0x0F);
}

TEST_F(EmulatorTest, STAX_B) {
    cpu.Reset(mem);
    cpu.B = 0x20;
    cpu.C = 0x0F;
    cpu.A = 0x1F;
    mem[0x0000] = INSTRUCTIONS::STAX_B;
    mem[0x0001] = 0x0A;
    mem[0x0002] = 0x20;
    cpu.Execute(2, mem);
    EXPECT_EQ(mem[0x200F], 0x1F);
}

TEST_F(EmulatorTest, STAX_D) {
    cpu.Reset(mem);
    cpu.D = 0x20;
    cpu.E = 0x0F;
    cpu.A = 0x1F;
    mem[0x0000] = INSTRUCTIONS::STAX_D;
    mem[0x0001] = 0x0A;
    mem[0x0002] = 0x20;
    cpu.Execute(2, mem);
    EXPECT_EQ(mem[0x200F], 0x1F);
}

TEST_F(EmulatorTest, SHLD_Address) {
    cpu.Reset(mem);
    cpu.L = 0x1F;
    cpu.H = 0x20;
    mem[0x0000] = INSTRUCTIONS::SHLD_ADDRESS;
    mem[0x0001] = 0x0F;
    mem[0x0002] = 0x20;
    cpu.Execute(5, mem);
    EXPECT_EQ(mem[0x200F], 0x1F);
    EXPECT_EQ(mem[0x2010], 0x20);
}

TEST_F(EmulatorTest, LDAX_B) {
    cpu.Reset(mem);
    cpu.B = 0x20;
    cpu.C = 0x0F;
    mem[0x200F] = 0x1F;
    mem[0x0000] = INSTRUCTIONS::LDAX_B;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.A, 0x1F);
}

TEST_F(EmulatorTest, LDAX_D) {
    cpu.Reset(mem);
    cpu.D = 0x20;
    cpu.E = 0x0F;
    mem[0x200F] = 0x1F;
    mem[0x0000] = INSTRUCTIONS::LDAX_D;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.A, 0x1F);
}

TEST_F(EmulatorTest, LHLD_Address) {
    cpu.Reset(mem);
    mem[0x200F] = 0x1F;
    mem[0x2010] = 0x20;
    mem[0x0000] = INSTRUCTIONS::LHLD_ADDRESS;
    mem[0x0001] = 0x0F;
    mem[0x0002] = 0x20;
    cpu.Execute(5, mem);
    EXPECT_EQ(cpu.L, 0x1F);
    EXPECT_EQ(cpu.H, 0x20);
}

TEST_F(EmulatorTest, XCHG) {
    cpu.Reset(mem);
    cpu.H = 0x30;
    cpu.L = 0x0A;
    cpu.D = 0x40;
    cpu.E = 0x00;
    mem[0x0000] = INSTRUCTIONS::XCHG;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.L, 0x00);
    EXPECT_EQ(cpu.H, 0x40);
    EXPECT_EQ(cpu.E, 0x0A);
    EXPECT_EQ(cpu.D, 0x30);
}

TEST_F(EmulatorTest, SPHL) {
    cpu.Reset(mem);
    cpu.H = 0x30;
    cpu.L = 0x0A;
    mem[0x0000] = INSTRUCTIONS::SPHL;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.SP, 0x300A);
}

TEST_F(EmulatorTest, XTHL) {
    cpu.Reset(mem);
    cpu.SP = 0x8000;
    cpu.H = 0x30;
    cpu.L = 0x0A;
    mem[0x8000] = 0x10;
    mem[0x8001] = 0x08;
    mem[0x0000] = INSTRUCTIONS::XTHL;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.L, 0x10);
    EXPECT_EQ(cpu.H, 0x08);
    EXPECT_EQ(mem[cpu.SP], 0x0A);
    EXPECT_EQ(mem[cpu.SP+1], 0x30);
}

TEST_F(EmulatorTest, PCHL) {
    cpu.Reset(mem);
    cpu.H = 0x30;
    cpu.L = 0x0A;
    mem[0x0000] = INSTRUCTIONS::PCHL;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.PC, 0x300A);
}

TEST_F(EmulatorTest, PUSH_B) {
    cpu.Reset(mem);
    cpu.B = 0x30;
    cpu.C = 0x0A;
    mem[0x0000] = INSTRUCTIONS::PUSH_B;
    cpu.Execute(4, mem);
    EXPECT_EQ(mem[0xFFFE], 0x30);
    EXPECT_EQ(mem[0xFFFD], 0x0A);
}

TEST_F(EmulatorTest, PUSH_D) {
    cpu.Reset(mem);
    cpu.D = 0x30;
    cpu.E = 0x0A;
    mem[0x0000] = INSTRUCTIONS::PUSH_D;
    cpu.Execute(4, mem);
    EXPECT_EQ(mem[0xFFFE], 0x30);
    EXPECT_EQ(mem[0xFFFD], 0x0A);
}

TEST_F(EmulatorTest, PUSH_H) {
    cpu.Reset(mem);
    cpu.H = 0x30;
    cpu.L = 0x0A;
    mem[0x0000] = INSTRUCTIONS::PUSH_H;
    cpu.Execute(4, mem);
    EXPECT_EQ(mem[0xFFFE], 0x30);
    EXPECT_EQ(mem[0xFFFD], 0x0A);
}

TEST_F(EmulatorTest, PUSH_PSW) {
    cpu.Reset(mem);
    cpu.flag.S = 0x01;
    cpu.flag.Z = 0x00;
    cpu.flag.AC = 0x00;
    cpu.flag.P = 0x00;
    cpu.flag.CY = 0x01;
    // [1000 0001] = 0x81 = 129
    cpu.A = 0x0A;
    mem[0x0000] = INSTRUCTIONS::PUSH_PSW;
    cpu.Execute(4, mem);
    EXPECT_EQ(mem[0xFFFE], 0x0A);
    EXPECT_EQ(mem[0xFFFD], 0x81);
}

TEST_F(EmulatorTest, POP_B) {
    cpu.Reset(mem);
    mem[0xFFFD] = 0x30;
    mem[0xFFFE] = 0x0A;
    cpu.SP = 0xFFFD;
    mem[0x0000] = INSTRUCTIONS::POP_B;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.C, 0x30);
    EXPECT_EQ(cpu.B, 0x0A);
}

TEST_F(EmulatorTest, POP_D) {
    cpu.Reset(mem);
    mem[0xFFFD] = 0x30;
    mem[0xFFFE] = 0x0A;
    cpu.SP = 0xFFFD;
    mem[0x0000] = INSTRUCTIONS::POP_D;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.E, 0x30);
    EXPECT_EQ(cpu.D, 0x0A);
}

TEST_F(EmulatorTest, POP_H) {
    cpu.Reset(mem);
    mem[0xFFFD] = 0x30;
    mem[0xFFFE] = 0x0A;
    cpu.SP = 0xFFFD;
    mem[0x0000] = INSTRUCTIONS::POP_H;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.L, 0x30);
    EXPECT_EQ(cpu.H, 0x0A);
}

TEST_F(EmulatorTest, POP_PSW) {
    cpu.Reset(mem);
    mem[0xFFFE] = 0x0A;
    // [1000 0001] = 0x81 = 129
    mem[0xFFFD] = 0x81;
    cpu.SP = 0xFFFD;
    mem[0x0000] = INSTRUCTIONS::POP_PSW;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
    EXPECT_EQ(cpu.A, 0x0A);
}

TEST_F(EmulatorTest, OUT_PORTADDRESS) {
    cpu.Reset(mem);
    mem[0x0000] = INSTRUCTIONS::MVI_A_DATA;
    mem[0x0001] = 0x01;
    mem[0x0002] = INSTRUCTIONS::OUT;
    mem[0x0003] = 0xFF;
    cpu.Execute(5, mem);
    EXPECT_EQ(cpu.A, 0x01);
    EXPECT_EQ(cpu.port.Data, 0x01);
    EXPECT_EQ(cpu.port.PortAddress, 0xFF);
    EXPECT_EQ(cpu.port.IO, 0x01);
    EXPECT_EQ(cpu.port.WR, 0x01);
}

TEST_F(EmulatorTest, IN_PORTADDRESS) {
    cpu.Reset(mem);
    cpu.port.Data = 0x05;
    mem[0x0000] = INSTRUCTIONS::IN;
    mem[0x0001] = 0xFF;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.A, 0x05);
    EXPECT_EQ(cpu.port.Data, 0x05);
    EXPECT_EQ(cpu.port.PortAddress, 0xFF);
    EXPECT_EQ(cpu.port.IO, 0x00);
    EXPECT_EQ(cpu.port.WR, 0x00);
}

TEST_F(EmulatorTest, CMP_A) {
    cpu.Reset(mem);
    cpu.A = 0x3F;
    mem[0x0000] = INSTRUCTIONS::CMP_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.A, 0x3F);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
}

TEST_F(EmulatorTest, CMP_B) {
    cpu.Reset(mem);
    cpu.A = 0x05;
    cpu.B = 0x0A;
    mem[0x0000] = INSTRUCTIONS::CMP_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.B, 0x0A);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x01);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_C) {
    cpu.Reset(mem);
    cpu.A = 0x3C;
    cpu.C = 0xC2;
    mem[0x0000] = INSTRUCTIONS::CMP_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.C, 0xC2);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_D) {
    cpu.Reset(mem);
    cpu.A = 0x7F;
    cpu.D = 0x81;
    mem[0x0000] = INSTRUCTIONS::CMP_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.D, 0x81);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_E) {
    cpu.Reset(mem);
    cpu.A = 0x0D;
    cpu.E = 0x45;
    mem[0x0000] = INSTRUCTIONS::CMP_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.E, 0x45);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_H) {
    cpu.Reset(mem);
    cpu.A = 0xCD;
    cpu.H = 0xFE;
    mem[0x0000] = INSTRUCTIONS::CMP_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.H, 0xFE);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x01);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_L) {
    cpu.Reset(mem);
    cpu.A = 0x00;
    cpu.L = 0xFF;
    mem[0x0000] = INSTRUCTIONS::CMP_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.L, 0xFF);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x01);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CMP_M) {
    cpu.Reset(mem);
    cpu.A = 0xCD;
    cpu.H = 0x20;
    cpu.L = 0x10;
    mem[0x2010] = 0xFE;
    mem[0x0000] = INSTRUCTIONS::CMP_M;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x2010], 0xFE);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x01);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, CPI_DATA) {
    cpu.Reset(mem);
    cpu.A = 0xCD;
    mem[0x0000] = INSTRUCTIONS::CPI_DATA;
    mem[0x0001] = 0xFE;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x01);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x01);
}

TEST_F(EmulatorTest, ANA_A) {
    cpu.Reset(mem);
    cpu.A = 0x00;
    mem[0x0000] = INSTRUCTIONS::ANA_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
}

TEST_F(EmulatorTest, DCR_A) {
    cpu.Reset(mem);
    cpu.A = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0xFF);
}

TEST_F(EmulatorTest, DCR_B) {
    cpu.Reset(mem);
    cpu.B = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.B, 0xFF);
}

TEST_F(EmulatorTest, DCR_C) {
    cpu.Reset(mem);
    cpu.C = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.C, 0xFF);
}

TEST_F(EmulatorTest, DCR_D) {
    cpu.Reset(mem);
    cpu.D = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.D, 0xFF);
}

TEST_F(EmulatorTest, DCR_E) {
    cpu.Reset(mem);
    cpu.E = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.E, 0xFF);
}

TEST_F(EmulatorTest, DCR_H) {
    cpu.Reset(mem);
    cpu.H = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.H, 0xFF);
}

TEST_F(EmulatorTest, DCR_L) {
    cpu.Reset(mem);
    cpu.L = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.L, 0xFF);
}

TEST_F(EmulatorTest, DCR_M) {
    cpu.Reset(mem);
    cpu.L = 0x00;
    cpu.H = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCR_M;
    cpu.Execute(3, mem);
    EXPECT_EQ(cpu.flag.S, 0x01);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(mem[0x8000], 0xFF);
}

TEST_F(EmulatorTest, DCX_B) {
    cpu.Reset(mem);
    cpu.C = 0x00;
    cpu.B = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCX_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0xFF);
}

TEST_F(EmulatorTest, DCX_D) {
    cpu.Reset(mem);
    cpu.E = 0x00;
    cpu.D = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCX_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0xFF);
}

TEST_F(EmulatorTest, DCX_H) {
    cpu.Reset(mem);
    cpu.L = 0x00;
    cpu.H = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCX_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0xFF);
}

TEST_F(EmulatorTest, DCX_SP) {
    cpu.Reset(mem);
    cpu.SP = 0x8000;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::DCX_SP;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0xFF);
}

TEST_F(EmulatorTest, INR_A) {
    cpu.Reset(mem);
    cpu.A = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.A, 0x00);
}

TEST_F(EmulatorTest, INR_B) {
    cpu.Reset(mem);
    cpu.B = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.B, 0x00);
}

TEST_F(EmulatorTest, INR_C) {
    cpu.Reset(mem);
    cpu.C = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.C, 0x00);
}

TEST_F(EmulatorTest, INR_D) {
    cpu.Reset(mem);
    cpu.D = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.D, 0x00);
}

TEST_F(EmulatorTest, INR_E) {
    cpu.Reset(mem);
    cpu.E = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.E, 0x00);
}

TEST_F(EmulatorTest, INR_H) {
    cpu.Reset(mem);
    cpu.H = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.H, 0x00);
}

TEST_F(EmulatorTest, INR_L) {
    cpu.Reset(mem);
    cpu.L = 0xFF;
    mem[0x0000] = INSTRUCTIONS::INR_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x01);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.L, 0x00);
}


TEST_F(EmulatorTest, INX_B) {
    cpu.Reset(mem);
    cpu.C = 0x00;
    cpu.B = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::INX_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0x01);
}

TEST_F(EmulatorTest, INX_D) {
    cpu.Reset(mem);
    cpu.E = 0x00;
    cpu.D = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::INX_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0x01);
}

TEST_F(EmulatorTest, INX_H) {
    cpu.Reset(mem);
    cpu.L = 0x00;
    cpu.H = 0x80;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::INX_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0x01);
}

TEST_F(EmulatorTest, INX_SP) {
    cpu.Reset(mem);
    cpu.SP = 0x8000;
    mem[0x8000] = 0x00;
    mem[0x0000] = INSTRUCTIONS::INX_SP;
    cpu.Execute(1, mem);
    EXPECT_EQ(mem[0x8000], 0x01);
}

TEST_F(EmulatorTest, ADD_A) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_B) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.B = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_C) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.C = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_D) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.D = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_E) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.E = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}


TEST_F(EmulatorTest, ADD_H) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.H = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_L) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.L = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADD_M) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.L = 0x00;
    cpu.H = 0x80;
    mem[0x8000] = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADD_M;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADI_DATA) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADI_DATA;
    mem[0x0001] = 0x14;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x01);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x28);
}

TEST_F(EmulatorTest, ADC_A) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_A;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_B) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.B = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_B;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_C) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.C = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_C;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_D) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.D = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_D;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_E) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.E = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_E;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_H) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.H = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_H;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_L) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.L = 0x14;
    cpu.flag.CY = 1;
    mem[0x0000] = INSTRUCTIONS::ADC_L;
    cpu.Execute(1, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}

TEST_F(EmulatorTest, ADC_M) {
    cpu.Reset(mem);
    cpu.A = 0x14;
    cpu.L = 0x14;
    cpu.H = 0x24;
    cpu.flag.CY = 1;
    mem[0x2414] = 0x14;
    mem[0x0000] = INSTRUCTIONS::ADC_A;
    cpu.Execute(2, mem);
    EXPECT_EQ(cpu.flag.S, 0x00);
    EXPECT_EQ(cpu.flag.Z, 0x00);
    EXPECT_EQ(cpu.flag.AC, 0x00);
    EXPECT_EQ(cpu.flag.P, 0x00);
    EXPECT_EQ(cpu.flag.CY, 0x00);
    EXPECT_EQ(cpu.A, 0x29);
}