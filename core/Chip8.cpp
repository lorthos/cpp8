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

            //SNE_VX_VY
        case 0x9000:
            if (getRegisters().V[Vx] != getRegisters().V[Vy]) {
                getRegisters().ProgramCounter += 2;
            }
            break;


        default:
            break;
    }
}

void Chip8::runInstruction8SET(unsigned short opcode) {
    bit8 Vx = (opcode >> 8) & 0x000f;
    bit8 Vy = (opcode >> 4) & 0x000f;
    bit8 lastDigit = opcode & 0x000f;
    bit16 buff;
    switch (lastDigit) {
        //8xy0 - LD Vx, Vy
        //Set Vx = Vy.
        case 0x00:
            getRegisters().V[Vx] = getRegisters().V[Vy];
            break;

            //8xy1 - OR Vx, Vy
            //Set Vx = Vx OR Vy.
        case 0x01:
            getRegisters().V[Vx] = getRegisters().V[Vx] | getRegisters().V[Vy];
            break;

            //8xy2 - AND Vx, Vy
            //Set Vx = Vx AND Vy.
        case 0x02:
            getRegisters().V[Vx] = getRegisters().V[Vx] & getRegisters().V[Vy];
            break;

            //8xy3 - XOR Vx, Vy
            //Set Vx = Vx XOR Vy.l
        case 0x03:
            getRegisters().V[Vx] = getRegisters().V[Vx] ^ getRegisters().V[Vy];
            break;

            //8xy4 - ADD Vx, Vy
            //Set Vx = Vx + Vy, set VF = carry.
        case 0x04:
            buff = getRegisters().V[Vx] + getRegisters().V[Vy];
            getRegisters().V[0x0f] = buff > 0xff ? 1 : 0;
            getRegisters().V[Vx] = buff;
            break;

            //8xy5 - SUB Vx, Vy
            //Set Vx = Vx - Vy, set VF = NOT borrow.
        case 0x05:
            getRegisters().V[0x0f] = getRegisters().V[Vx] > getRegisters().V[Vy] ? 1 : 0;
            getRegisters().V[Vx] = getRegisters().V[Vx] - getRegisters().V[Vy];
            break;

            //8xy6 - SHR Vx {, Vy}
            //Set Vx = Vx SHR 1.
        case 0x06:
            getRegisters().V[0x0f] = getRegisters().V[Vx] & 0x01;
            getRegisters().V[Vx] /= 2;
            break;

            //8xy7 - SUBN Vx, Vy
            //Set Vx = Vy - Vx, set VF = NOT borrow.
        case 0x07:
            getRegisters().V[0x0f] = getRegisters().V[Vy] > getRegisters().V[Vx];
            getRegisters().V[Vx] = getRegisters().V[Vy] - getRegisters().V[Vx];
            break;

            //8xyE - SHL Vx {, Vy}
            //Set Vx = Vx SHL 1.
        case 0x0E:
            getRegisters().V[0x0f] = (getRegisters().V[Vx] & 0b10000000) ? 1 : 0;
            getRegisters().V[Vx] *= 2;
            break;

    }
}



