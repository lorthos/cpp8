//
// Created by lorthos on 15.03.21.
//

#include "Memory.h"
#include <assert.h>
#include <algorithm>

Memory::Memory() {
    std::fill_n(mMemory, MEMORY_SIZE, 0);
    std::memcpy(&mMemory, mDefaultSprites, sizeof(mDefaultSprites));
}


void Memory::mSet(int index, unsigned char val) {
    mPrecondition(index);
    mMemory[index] = val;
}

unsigned char Memory::mGet(int index) {
    mPrecondition(index);
    return mMemory[index];
}

void Memory::mPrecondition(int index) {
    assert(index >= 0 && index < MEMORY_SIZE);
}
