#pragma once

class Chip8 {


public:
    static const int MEMORY_SIZE = 4096;
    static const int DISPLAY_WIDTH = 64;
    static const int DISPLAY_HEIGHT = 32;

    //memory
    void mSet(int index, unsigned char val);
    unsigned char mGet(int index);



private:
    /**
     * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#memmap
     *
     * capable of accessing up to 4KB (4,096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095).
     */
    unsigned char mMemory[MEMORY_SIZE];
    //memory
    static void mPrecondition(int index);
};
