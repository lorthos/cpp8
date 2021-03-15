//
// Created by lorthos on 15.03.21.
//

#include <assert.h>
#include "Keyboard.h"

void Keyboard::kDown(int key) {
    checkState(key);
    state[key] = true;
}

void Keyboard::kUp(int key) {
    checkState(key);
    state[key] = false;
}

bool Keyboard::kIsDown(int key) {
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

