#include "Memory.h"
#include <assert.h>
#include <algorithm>

Memory::Memory() {
    std::fill_n(heap, MEMORY_SIZE, 0);
    std::memcpy(&heap, mDefaultSprites, sizeof(mDefaultSprites));
}


void Memory::set(int index, unsigned char val) {
    mPrecondition(index);
    heap[index] = val;
}

unsigned char Memory::get(int index) {
    mPrecondition(index);
    return heap[index];
}

void Memory::mPrecondition(int index) {
    assert(index >= 0 && index < MEMORY_SIZE);
}

void Memory::copyFrom(const char *rom, long size, int startAddress) {
    std::memcpy(&heap[startAddress], rom, size);
}

bit16 Memory::getOpCode(int index) {
    bit8 byte1 = get(index);
    bit8 byte2 = get(index + 1);
    return byte1 << 8 | byte2;
}
