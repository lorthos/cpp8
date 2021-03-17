#include <assert.h>
#include "Keyboard.h"
#include <algorithm>

Keyboard::Keyboard() {
    std::fill_n(state, KEYBOARD_SIZE, false);
}

void Keyboard::setDown(int key) {
    checkState(key);
    state[key] = true;
}

void Keyboard::setUp(int key) {
    checkState(key);
    state[key] = false;
}

bool Keyboard::IsDown(int key) {
    checkState(key);
    return state[key];
}

void Keyboard::checkState(int key) {
    assert(0 <= key && key < KEYBOARD_SIZE);
}

int Keyboard::lookUpDesktopKey(int desktopKey) {
    for (int i = 0; i < KEYBOARD_SIZE; i++) {
        if (desktopBindings[i] == desktopKey) {
            return i;
        }
    }
    return -1;
}

int Keyboard::waitForKeyPress() {
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type != SDL_KEYDOWN) {
            continue;
        }
        int k = event.key.keysym.sym;
        return lookUpDesktopKey(k);
    }
    return 0;
}


