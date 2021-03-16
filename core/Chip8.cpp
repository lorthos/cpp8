#include <cassert>
#include "Chip8.h"
#include <fstream>

#define LOAD_ADDRESS 0x200

Chip8::Chip8() {

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

void Chip8::loadRom(const char *rom, long size) {
    loadPrecondition(size);
    mMemory.copyTo(rom, size, LOAD_ADDRESS);
    getRegisters().ProgramCounter = LOAD_ADDRESS;
}

void Chip8::loadPrecondition(long size) {
    assert(size + LOAD_ADDRESS < Memory::MEMORY_SIZE);

}

std::pair<char *, long> Chip8::readRom(const std::string &romPath) {
    FILE *f = std::fopen(romPath.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *contents = (char *) malloc(fsize + 1);
    fread(contents, fsize, 1, f);
    fclose(f);

    contents[fsize] = 0;
    return std::pair<char *, long>{contents, fsize};
}


