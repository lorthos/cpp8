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

void Chip8::tick() {
    unsigned short opCode = getMemory().getOpCode(getRegisters().ProgramCounter);
    getRegisters().ProgramCounter += 2;
    runInstruction(opCode);
}

void Chip8::runInstruction(unsigned short opcode) {
    switch (opcode) {

        //00E0 - CLS
        //Clear the display.
        case 0x00E0:
            getDisplay().clear();
            break;

            //00EE - RET
            //Return from a subroutine.
        case 0x00EE:
            getRegisters().ProgramCounter = sPop();
            break;

        default:
            runInstructionBasic(opcode);
            break;
    }
}

/**
 * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
 *
 * @param opcode
 */
void Chip8::runInstructionBasic(unsigned short opcode) {
    bit16 nnn = opcode & 0x0fff; //mask 4, extract 12 bits
    bit8 Vx = (opcode >> 8) & 0x000f;
    bit8 Vy = (opcode >> 4) & 0x000f;
    bit8 kk = opcode & 0x00ff;
    switch (opcode & 0xf000) {
        //1nnn - JP addr
        //Jump to location nnn.
        case 0x1000:
            getRegisters().ProgramCounter = nnn;
            break;

            //2nnn - CALL addr
            //Call subroutine at nnn.
        case 0x2000:
            sPush(getRegisters().ProgramCounter);
            getRegisters().ProgramCounter = nnn;
            break;

            //3xkk - SE Vx, byte
            //Skip next instruction if Vx = kk.
        case 0x3000:
            if (getRegisters().V[Vx] == kk) {
                getRegisters().ProgramCounter += 2;
            }
            break;

            //4xkk - SNE Vx, byte
            //Skip next instruction if Vx != kk.
        case 0x4000:
            if (getRegisters().V[Vx] != kk) {
                getRegisters().ProgramCounter += 2;
            }
            break;


            // 5xy0 - SE Vx, Vy
            // Skip next instruction if Vx = Vy.
        case 0x5000:
            if (getRegisters().V[Vx] == getRegisters().V[Vy]) {
                getRegisters().ProgramCounter += 2;
            }
            break;

            //6xkk - LD Vx, byte
            //Set Vx = kk.
        case 0x6000:
            getRegisters().V[Vx] = kk;
            break;

            //7xkk - ADD Vx, byte
            //Set Vx = Vx + kk.
        case 0x7000:
            getRegisters().V[Vx] += kk;
            break;

        case 0x8000:
            runInstruction8SET(opcode);
            break;

        default:
            break;
    }
}

void Chip8::runInstruction8SET(unsigned short opcode) {
    bit8 Vx = (opcode >> 8) & 0x000f;
    bit8 Vy = (opcode >> 4) & 0x000f;
    bit8 lastDigit = opcode & 0x000f;
    switch (lastDigit) {
        //8xy0 - LD Vx, Vy
        //Set Vx = Vy.
        case 0x00:
            getRegisters().V[Vx] = getRegisters().V[Vy];
            break;

        case 0x01:
            getRegisters().V[Vx] = getRegisters().V[Vx] | getRegisters().V[Vy];
            break;

    }
}



