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
    bit16 IRegister = 0;
    bit16 ProgramCounter = 0;
    //TODO can be removed
    bit8 StackPointer = 0;
    bit8 SoundTimer = 0;
    bit8 DelayTimer = 0;

    Registers();
};
