#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "Chip8.h"


TEST_CASE("Memory Round trip") {
    Chip8 c8{};
    c8.mSet(42, 'A');
    unsigned char readValue = c8.mGet(42);
    REQUIRE(readValue == 'A');
}

TEST_CASE("Memory Boundaries") {
    Chip8 c8{};
//    CHECK_THROWS(c8.mSet(424242, 'A'));
}

TEST_CASE("Register Round trip") {
    Chip8 c8{};
    c8.getRegisters().V[0] = 42;
    REQUIRE(c8.getRegisters().V[0] == 42);

    c8.getRegisters().V[0x0f] = 43;
    REQUIRE(c8.getRegisters().V[15] == 43);
}


