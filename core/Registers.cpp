//
// Created by lorthos on 15.03.21.
//

#include "Registers.h"
#include <algorithm>

Registers::Registers() {
    std::fill_n(V, 16, 0);
}
