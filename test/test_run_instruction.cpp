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
