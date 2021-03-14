#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "GameMath.h"

using namespace GameMath;

TEST_CASE("Summation") {
    int a = 1;
    int b = 2;
    int c = 3;

    REQUIRE(c == GameMath::sum(a, b));

}


