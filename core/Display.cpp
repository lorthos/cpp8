//
// Created by lorthos on 15.03.21.
//

#include "Display.h"
#include <algorithm>
#include <assert.h>


Display::Display() {
    for (int i = 0; i < DISPLAY_HEIGHT; ++i) {
        std::fill_n(screenBuffer[i], DISPLAY_WIDTH, false);
    }
}

void Display::dSet(int x, int y) {
    preCondition(x, y);
    screenBuffer[y][x] = true;
}

bool Display::dIsSet(int x, int y) {
    preCondition(x, y);
    return screenBuffer[y][x];
}

void Display::preCondition(int x, int y) {
    assert(0 <= x && x < DISPLAY_WIDTH && 0 <= y && y <= DISPLAY_HEIGHT);
}

void Display::Draw(SDL_Renderer *renderer) {
    for (int x = 0; x < DISPLAY_WIDTH; ++x) {
        for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
            if (dIsSet(x, y)) {
                SDL_Rect r{};
                r.x = x * DISPLAY_SCALE_FACTOR;
                r.y = y * DISPLAY_SCALE_FACTOR;
                r.w = DISPLAY_SCALE_FACTOR;
                r.h = DISPLAY_SCALE_FACTOR;

                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
}
