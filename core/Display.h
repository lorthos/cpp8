#pragma once

#include <SDL.h>
#include <SDL_system.h>

class Display {

public:
    Display();

    void Draw(SDL_Renderer *renderer);

    void dSet(int x, int y);

    bool dIsSet(int x, int y);

    static const int DISPLAY_WIDTH = 64;
    static const int DISPLAY_HEIGHT = 32;
    static const int DISPLAY_SCALE_FACTOR = 10;

private:
    bool screenBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];

    void preCondition(int x, int y);
};