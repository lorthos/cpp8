#include <cassert>
#include "Chip8.h"

void Chip8::mSet(int index, unsigned char val) {
    mPrecondition(index);
    mMemory[index] = val;
}

unsigned char Chip8::mGet(int index) {
    mPrecondition(index);
    return mMemory[index];
}

void Chip8::mPrecondition(int index) {
    assert(index >= 0 && index < MEMORY_SIZE);
}
