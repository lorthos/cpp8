#pragma once

#include <unordered_map>
#include <SDL.h>
#include <SDL_system.h>

/**
 * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.3
 */
class Keyboard {
public:
    static const int KEYBOARD_SIZE = 16;

    Keyboard();

    void setDown(int key);

    void setUp(int key);

    bool IsDown(int key);

    int lookUpDesktopKey(int desktopKey);

    int waitForKeyPress();

private:
    static void checkState(int key);

    bool state[KEYBOARD_SIZE];
    int desktopBindings[KEYBOARD_SIZE]
            {SDLK_0,
             SDLK_1,
             SDLK_2,
             SDLK_3,
             SDLK_4,
             SDLK_5,
             SDLK_6,
             SDLK_7,
             SDLK_8,
             SDLK_9,
             SDLK_a,
             SDLK_b,
             SDLK_c,
             SDLK_d,
             SDLK_e,
             SDLK_f};
};

