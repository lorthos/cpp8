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

    static const int STACK_SIZE = 16;

    Chip8();

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

    //memory
    Memory mMemory;
    //registers
    Registers mRegisters;

    //stack
    std::stack<bit16> mStack;
    void checkStackBoundary();

    //keyboard
    Keyboard mKeyboard;

    //display
    Display mDisplay;

};
