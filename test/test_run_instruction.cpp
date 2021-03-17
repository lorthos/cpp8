#define private public

#include "catch.hpp"
#include "Chip8.h"


TEST_CASE("run instruction JP") {
    Chip8 c8{};
    c8.runInstruction(0x1ff2);
    REQUIRE(0x0ff2 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("run instruction CALL") {
    Chip8 c8{};
    c8.runInstruction(0x1ff1);
    c8.runInstruction(0x2ff2);
    REQUIRE(0x0ff2 == c8.getRegisters().ProgramCounter);
    REQUIRE(0x0ff1 == c8.sPop());
}

TEST_CASE("run instruction SE Vx Byte") {
    Chip8 c8{};
    c8.runInstruction(0x1001);
    c8.runInstruction(0x3000);
    //compare 0 to 0 which should incr by 2
    REQUIRE(0x0003 == c8.getRegisters().ProgramCounter);

    c8.runInstruction(0x3005);
    //compare 0 to 5 which should not incr
    REQUIRE(0x0003 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("run instruction SNE Vx Byte") {
    Chip8 c8{};
    c8.runInstruction(0x1001);
    c8.runInstruction(0x4001);
    //compare 0 to 1 which should incr by 2
    REQUIRE(0x0003 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("run instruction SE Vx Vy") {
    Chip8 c8{};
    c8.runInstruction(0x1001);
    c8.runInstruction(0x5010);
    REQUIRE(0x0003 == c8.getRegisters().ProgramCounter);
    c8.getRegisters().V[3] = 1;
    c8.getRegisters().V[4] = 2;
    c8.runInstruction(0x5340);
    REQUIRE(0x0003 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("run instruction LD Vx, byte") {
    Chip8 c8{};
    c8.runInstruction(0x6605);
    REQUIRE(c8.getRegisters().V[6] == 5);
}

TEST_CASE("run instruction ADD Vx, byte") {
    Chip8 c8{};
    c8.runInstruction(0x7302);
    REQUIRE(c8.getRegisters().V[3] == 2);
    c8.runInstruction(0x7302);
    REQUIRE(c8.getRegisters().V[3] == 4);
}

TEST_CASE("run instruction LD Vx, Vy") {
    Chip8 c8{};
    c8.getRegisters().V[7] = 7;
    c8.runInstruction(0x8070);
    REQUIRE(c8.getRegisters().V[0] == 7);
}

TEST_CASE("run instruction OR Vx, Vy") {
    Chip8 c8{};
    c8.getRegisters().V[1] = 1;
    c8.runInstruction(0x8011);
    REQUIRE(c8.getRegisters().V[0] == 1);
}

TEST_CASE("run instruction AND Vx, Vy") {
    Chip8 c8{};
    c8.getRegisters().V[0] = 1;
    c8.runInstruction(0x8012);
    REQUIRE(c8.getRegisters().V[0] == 0);
}

TEST_CASE("run instruction XOR Vx, Vy") {
    Chip8 c8{};
    c8.getRegisters().V[1] = 1;
    c8.runInstruction(0x8013);
    REQUIRE(c8.getRegisters().V[0] == 1);
}

TEST_CASE("run instruction ADD Vx, Vy, carry = 0") {
    Chip8 c8{};
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    c8.getRegisters().V[0] = 0x01;
    c8.getRegisters().V[1] = 0x02;
    c8.runInstruction(0x8014);
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    REQUIRE(c8.getRegisters().V[0] == 3);
}

TEST_CASE("run instruction ADD Vx, Vy, carry = 1") {
    Chip8 c8{};
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    c8.getRegisters().V[0] = 200;
    c8.getRegisters().V[1] = 200;
    c8.runInstruction(0x8014);
    REQUIRE(c8.getRegisters().V[0x0f] == 1);
    REQUIRE(c8.getRegisters().V[0] == (400 & 0x00ff));
}

TEST_CASE("run instruction SUB Vx, Vy, borrow = 1") {
    //set VF = Not borrow
    Chip8 c8{};
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    c8.getRegisters().V[0] = 200;
    c8.getRegisters().V[1] = 100;
    c8.runInstruction(0x8015);
    REQUIRE(c8.getRegisters().V[0x0f] == 1);
    REQUIRE(c8.getRegisters().V[0] == 100);
}

TEST_CASE("run instruction SUB Vx, Vy, borrow = 0") {
    //set VF = Not borrow
    Chip8 c8{};
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    c8.getRegisters().V[0] = 0;
    c8.getRegisters().V[1] = 6;
    c8.runInstruction(0x8015);
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    REQUIRE(c8.getRegisters().V[0] == 0xfa); //256-6 = 250
}

TEST_CASE("run instruction SHR Vx {, Vy}, no remainder") {
    //set VF = Not borrow
    Chip8 c8{};
    c8.getRegisters().V[0] = 10;
    c8.getRegisters().V[1] = 2;
    c8.runInstruction(0x8016);
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    REQUIRE(c8.getRegisters().V[0] == 0x05);
}

TEST_CASE("run instruction SHR Vx {, Vy} with remainder") {
    //set VF = Not borrow
    Chip8 c8{};
    c8.getRegisters().V[0] = 11;
    c8.getRegisters().V[1] = 2;
    c8.runInstruction(0x8016);
    REQUIRE(c8.getRegisters().V[0x0f] == 1);
    REQUIRE(c8.getRegisters().V[0] == 0x05);
}

TEST_CASE("run instruction SUBN Vx, Vy, no borrow") {
    //set VF = Not borrow
    Chip8 c8{};
    c8.getRegisters().V[0] = 2;
    c8.getRegisters().V[1] = 5;
    c8.runInstruction(0x8017);
    REQUIRE(c8.getRegisters().V[0x0f] == 1);
    REQUIRE(c8.getRegisters().V[0] == 0x03);
}

TEST_CASE("run instruction SUBN Vx, Vy, with borrow") {
    //set VF = Not borrow
    Chip8 c8{};
    c8.getRegisters().V[0] = 5;
    c8.getRegisters().V[1] = 2;
    c8.runInstruction(0x8017);
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    REQUIRE(c8.getRegisters().V[0] == 0xfd);
}

TEST_CASE("run instruction SHL Vx {, Vy} vf=0") {
    //set VF = Not borrow
    Chip8 c8{};
    c8.getRegisters().V[0] = 0b00000010;
    c8.runInstruction(0x800E);
    REQUIRE(c8.getRegisters().V[0x0f] == 0);
    REQUIRE(c8.getRegisters().V[0] == 0x04);
}

TEST_CASE("run instruction SHL Vx {, Vy} vf=1") {
    //If the most-significant bit of Vx is 1, then VF is set to 1,
    // otherwise to 0. Then Vx is multiplied by 2.
    Chip8 c8{};
    c8.getRegisters().V[0] = 0b10000001;
    c8.runInstruction(0x801E);
    REQUIRE(c8.getRegisters().V[0x0f] == 1);
    REQUIRE(c8.getRegisters().V[0] == 0b00000010);
}


TEST_CASE("run instruction SNE_VX_VY, not equal") {
    Chip8 c8{};
    c8.getRegisters().V[0] = 0;
    c8.getRegisters().V[1] = 1;
    c8.runInstruction(0x1ff1);
    c8.runInstruction(0x9010);
    REQUIRE(0x0ff3 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("run instruction SNE_VX_VY, equal") {
    Chip8 c8{};
    c8.getRegisters().V[0] = 0;
    c8.getRegisters().V[1] = 0;
    c8.runInstruction(0x1ff1);
    c8.runInstruction(0x9010);
    REQUIRE(0x0ff1 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("get rand") {
    Chip8 c8{};
    for (int i = 0; i < 500; ++i) {
        unsigned char x = c8.getRand();
        REQUIRE(0 <= x);
        REQUIRE(x < 256);
    }
}

TEST_CASE("draw instruction") {
    Chip8 c8{};
    c8.getRegisters().IRegister = 0;
    c8.getRegisters().V[0] = 50;
    c8.getRegisters().V[2] = 50;
    c8.runInstruction(0xD025);
}

TEST_CASE("0x33") {
    Chip8 c8{};
    c8.getRegisters().IRegister = 0x201;//hope its empty
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister) == 0);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 1) == 0);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 2) == 0);
    c8.getRegisters().V[0] = 128;
    c8.runInstruction(0xF033);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister) == 1);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 1) == 2);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 2) == 8);

}

TEST_CASE("0x55") {
    Chip8 c8{};
    c8.getRegisters().IRegister = 0x201;//hope its empty
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister) == 0);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 1) == 0);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 2) == 0);
    c8.getRegisters().V[0] = 0;
    c8.getRegisters().V[1] = 1;
    c8.getRegisters().V[2] = 2;
    c8.runInstruction(0xF255);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister) == 0);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 1) == 1);
    REQUIRE(c8.getMemory().get(c8.getRegisters().IRegister + 2) == 2);
}

TEST_CASE("0x65") {
    Chip8 c8{};
    c8.getRegisters().IRegister = 0x201;//hope its empty
    c8.getMemory().set(c8.getRegisters().IRegister, 5);
    c8.getMemory().set(c8.getRegisters().IRegister + 1, 6);
    c8.getMemory().set(c8.getRegisters().IRegister + 2, 7);
    c8.getRegisters().V[0] = 0;
    c8.getRegisters().V[1] = 0;
    c8.getRegisters().V[2] = 0;
    c8.runInstruction(0xF265);
    REQUIRE(c8.getRegisters().V[0] == 5);
    REQUIRE(c8.getRegisters().V[1] == 6);
    REQUIRE(c8.getRegisters().V[2] == 7);
}





