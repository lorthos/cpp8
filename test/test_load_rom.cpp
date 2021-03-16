#include "catch.hpp"
#include "Chip8.h"


TEST_CASE("load rom") {
    Chip8 c8{};
    REQUIRE(0 == c8.getRegisters().ProgramCounter);
    c8.loadRom("rom1", sizeof("rom1"));
    REQUIRE(0x200 == c8.getRegisters().ProgramCounter);
}

TEST_CASE("load rom from file") {
    Chip8 c8{};
    const std::pair<char *, long> &pair = Chip8::readRom("./roms/test.txt");
    REQUIRE(5 == pair.second);
    REQUIRE(std::string(pair.first) == "12345");
    c8.loadRom(pair.first, pair.second);
    REQUIRE('1' == c8.getMemory().mGet(0x200));
    REQUIRE('2' == c8.getMemory().mGet(0x201));
    REQUIRE('3' == c8.getMemory().mGet(0x202));
    REQUIRE('4' == c8.getMemory().mGet(0x203));
    REQUIRE('5' == c8.getMemory().mGet(0x204));
    REQUIRE(0 == c8.getMemory().mGet(0x205));
}