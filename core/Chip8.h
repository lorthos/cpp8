#pragma once
#define bit8 unsigned char
#define bit16 unsigned short

/**
 * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.2
 */
class Registers {
public:
    // 16 general purpose 8-bit registers
    bit8 V[16];
    bit16 IRegister;
    bit16 ProgramCounter;
    bit8 StackPointer;
    bit8 SoundTimer;
    bit8 DelayTimer;
};

class Chip8 {


public:
    static const int MEMORY_SIZE = 4096;
    static const int DISPLAY_WIDTH = 64;
    static const int DISPLAY_HEIGHT = 32;

    //memory
    void mSet(int index, unsigned char val);

    unsigned char mGet(int index);

    //registers
    [[nodiscard]] Registers &getRegisters() {
        return mRegisters;
    };


private:
    //memory
    /**
     * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#memmap
     *
     * capable of accessing up to 4KB (4,096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095).
     */
    unsigned char mMemory[MEMORY_SIZE];

    static void mPrecondition(int index);

    //registers
    Registers mRegisters;
};
