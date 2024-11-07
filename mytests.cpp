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

TEST_F(EmulatorTest, LDA) {
    cpu.Reset(mem);
    mem[0x000A] = 0x0F;
    mem[0x0000] = INSTRUCTIONS::LDA;
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