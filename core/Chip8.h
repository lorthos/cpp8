#pragma once
#define bit8 unsigned char
#define bit16 unsigned short

#include <stack>
#include "Keyboard.h"
#include "Registers.h"



class Chip8 {
public:
    static const int MEMORY_SIZE = 4096;
    static const int STACK_SIZE = 16;
    static const int DISPLAY_WIDTH = 64;
    static const int DISPLAY_HEIGHT = 32;

    Chip8();

    //memory
    void mSet(int index, unsigned char val);

    unsigned char mGet(int index);

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


private:
    //memory
    /**
     * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#memmap
     *
     * capable of accessing up to 4KB (4,096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095).
     */
    bit8 mMemory[MEMORY_SIZE];

    static void mPrecondition(int index);

    //registers
    Registers mRegisters;

    //stack
    std::stack<bit16> mStack;

    void checkStackBoundary();

    //keyboard
    Keyboard mKeyboard;

    //default sprites
    static constexpr char mDefaultSprites[] = {
            0xf0, 0x90, 0x90, 0x90, 0xf0,
            0x20, 0x60, 0x20, 0x20, 0x70,
            0xf0, 0x10, 0xf0, 0x80, 0xf0,
            0xf0, 0x10, 0xf0, 0x10, 0xf0,
            0x90, 0x90, 0xf0, 0x10, 0x10,
            0xf0, 0x80, 0xf0, 0x10, 0xf0,
            0xf0, 0x80, 0xf0, 0x90, 0xf0,
            0xf0, 0x10, 0x20, 0x40, 0x40,
            0xf0, 0x90, 0xf0, 0x90, 0xf0,
            0xf0, 0x90, 0xf0, 0x10, 0xf0,
            0xf0, 0x90, 0xf0, 0x90, 0x90,
            0xe0, 0x90, 0xe0, 0x90, 0xe0,
            0xf0, 0x80, 0x80, 0x80, 0xf0,
            0xe0, 0x90, 0x90, 0x90, 0xe0,
            0xf0, 0x80, 0xf0, 0x80, 0xf0,
            0xf0, 0x80, 0xf0, 0x80, 0x80
    };

};
