#pragma once
#define bit8 unsigned char
#define bit16 unsigned short

#include <stack>
#include "Memory.h"
#include "Keyboard.h"
#include "Registers.h"
#include "Display.h"



class Chip8 {
public:
    Chip8();
    void tick();
    static std::pair<char *, long> readRom(const std::string& romPath);
    void loadRom(const char *rom, long size);

    static const int STACK_SIZE = 16;

    //memory
    Memory &getMemory() {
        return mMemory;
    };

    //registers
    [[nodiscard]] Registers &getRegisters() {
        return mRegisters;
    };

    //stack
    void sPush(bit16 val);

    bit16 sPop();

    int sSize() { return mStack.size(); };

    //keyboard
    Keyboard &getKeyboard() {
        return mKeyboard;
    };

    //display
    Display &getDisplay() {
        return mDisplay;
    };

private:
    void loadPrecondition(long size);
    void runInstruction(bit16 opcode);
    void runInstructionBasic(bit16 opcode);
    void runInstruction8SET(bit16 opcode);
    void gotoNextInstruction();
    void runInstructionFSET(bit16 opcode);

    //memory
    Memory mMemory{};
    //registers
    Registers mRegisters;

    //stack
    std::stack<bit16> mStack;

    void checkStackBoundary();

    //keyboard
    Keyboard mKeyboard;

    //display
    Display mDisplay;

    //random
    bit8 getRand();


};
