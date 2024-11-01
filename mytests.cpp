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


