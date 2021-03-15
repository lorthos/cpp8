#include <cassert>
#include "Chip8.h"

Chip8::Chip8() {
    std::fill_n(mMemory, MEMORY_SIZE, 0);
    std::memcpy(mMemory, mDefaultSprites, sizeof(mDefaultSprites));
}

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

void Chip8::sPush(bit16 val) {
    mStack.push(val);
    checkStackBoundary();
    mRegisters.StackPointer++;
}

bit16 Chip8::sPop() {
    auto val = mStack.top();
    mStack.pop();
    mRegisters.StackPointer--;
    return val;
}

void Chip8::checkStackBoundary() {
    assert(mStack.size() <= STACK_SIZE);
}

