#pragma once

#include <SDL.h>
#include <SDL_system.h>
#include "Memory.h"

class Display {

public:
    Display();

    void Render(SDL_Renderer *renderer);

    bool DrawSprite(int x, int y, int spriteStart, int spriteSize, Memory &memory);

    void dSet(int x, int y);

    bool dIsSet(int x, int y);

    static const int DISPLAY_WIDTH = 64;
    static const int DISPLAY_HEIGHT = 32;
    static const int DISPLAY_SCALE_FACTOR = 10;

private:
    bool screenBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];

    void preCondition(int x, int y);
};
