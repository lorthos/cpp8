#include <SDL.h>
#include <SDL_system.h>
#include <string>
#include "Chip8.h"

SDL_Window *mWindow;
SDL_Renderer *mRenderer;
const int DISPLAY_SCALE_FACTOR = 10;
const std::string DISPLAY_WINDOW_TITLE = "CPP8";
Chip8 c8{};

bool InitializeWindow(int xres, int yres) {
    mWindow = SDL_CreateWindow(
            DISPLAY_WINDOW_TITLE.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            xres,
            yres,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_TEXTUREACCESS_TARGET);


    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Draw() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 51, 255, 102, 0);
    SDL_Rect r{};
    r.x = 0;
    r.y = 0;
    r.w = 32;
    r.h = 32;
    SDL_RenderFillRect(mRenderer, &r);
    SDL_RenderPresent(mRenderer);
}

int main(int argc, char **argv) {

    InitializeWindow(Chip8::DISPLAY_WIDTH * DISPLAY_SCALE_FACTOR, Chip8::DISPLAY_HEIGHT * DISPLAY_SCALE_FACTOR);
    bool mIsRunning = true;

    while (mIsRunning) {
        // process input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    mIsRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (SDLK_ESCAPE == event.key.keysym.sym) {
                        mIsRunning = false;
                        break;
                    }
                    auto c8KeyDown = c8.getKeyboard().lookUpDesktopKey(event.key.keysym.sym);
                    if (-1 != c8KeyDown) {
                        c8.getKeyboard().kDown(c8KeyDown);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    auto c8KeyUp = c8.getKeyboard().lookUpDesktopKey(event.key.keysym.sym);
                    if (-1 != c8KeyUp) {
                        c8.getKeyboard().kUp(c8KeyUp);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        // update state
        // generate output
        Draw();
    }


    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();

    return 0;
}
