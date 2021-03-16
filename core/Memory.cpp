//
// Created by lorthos on 15.03.21.
//

#include "Memory.h"
#include <assert.h>
#include <algorithm>

Memory::Memory() {
    std::fill_n(heap, MEMORY_SIZE, 0);
    std::memcpy(&heap, mDefaultSprites, sizeof(mDefaultSprites));
}


void Memory::mSet(int index, unsigned char val) {
    mPrecondition(index);
    heap[index] = val;
}

unsigned char Memory::mGet(int index) {
    mPrecondition(index);
    return heap[index];
}

void Memory::mPrecondition(int index) {
    assert(index >= 0 && index < MEMORY_SIZE);
}

void Memory::copyTo(const char *rom, long size, int startAddress) {
    std::memcpy(&heap[startAddress], rom, size);
}
