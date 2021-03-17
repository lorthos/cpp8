#include "Display.h"
#include <algorithm>
#include <assert.h>


Display::Display() {
    clear();
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

void Display::Render(SDL_Renderer *renderer) {
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

bool Display::DrawSprite(int x, int y, int spriteStart, int spriteSize, Memory &memory) {
    bool pixelChanged = false;

    for (int ly = 0; ly < spriteSize; ++ly) {
        unsigned char c = memory.get(spriteStart + ly);
        for (int lx = 0; lx < 8; ++lx) {
            if ((c & (0b10000000 >> lx)) == 0) {
                continue;
            }

            if (screenBuffer[(ly + y) % DISPLAY_HEIGHT][(lx + x) % DISPLAY_WIDTH]) {
                pixelChanged = true;
            }

            screenBuffer[(ly + y) % DISPLAY_HEIGHT][(lx + x) % DISPLAY_WIDTH] ^= true;
        }
    }
    return pixelChanged;
}

void Display::clear() {
    for (int i = 0; i < DISPLAY_HEIGHT; ++i) {
        std::fill_n(screenBuffer[i], DISPLAY_WIDTH, false);
    }
}
