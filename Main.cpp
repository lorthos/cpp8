#include <SDL.h>
#include <SDL_system.h>
#include <SDL_mixer.h>
#include <string>
#include "Chip8.h"
#include "Display.h"

SDL_Window *mWindow;
SDL_Renderer *mRenderer;
const std::string DISPLAY_WINDOW_TITLE = "CPP8";
Chip8 c8{};
Mix_Chunk *beepSound = NULL;


bool InitializeAudio(std::string wavPath) {
    SDL_AudioSpec wavSpec;
    SDL_Init(SDL_INIT_AUDIO);

    //Initialize SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        return false;
    }

    //Load the sound effects
    beepSound = Mix_LoadWAV(wavPath.c_str());
    //If there was a problem loading the sound effects
    if (beepSound == nullptr) {
        return false;
    }

    return true;
}


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

void Update() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 51, 255, 102, 0);

    c8.getDisplay().Render(mRenderer);
    SDL_RenderPresent(mRenderer);

    if (c8.getRegisters().DelayTimer > 0) {
        SDL_Delay(10);
        c8.getRegisters().DelayTimer--;
    }
    if (c8.getRegisters().SoundTimer > 0) {
        SDL_Delay(10);
        Mix_PlayChannel(-1, beepSound, 0);
        c8.getRegisters().SoundTimer--;
    }

    unsigned short opCode = c8.getMemory().getOpCode(c8.getRegisters().ProgramCounter);
    c8.runInstruction(opCode);
    c8.getRegisters().ProgramCounter += 2;
}

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_EVERYTHING);

    InitializeWindow(Display::DISPLAY_WIDTH * Display::DISPLAY_SCALE_FACTOR,
                     Display::DISPLAY_HEIGHT * Display::DISPLAY_SCALE_FACTOR);
    InitializeAudio("./assets/sfx_sounds_Blip1.wav");
    bool mIsRunning = true;

    const std::pair<char *, long> &pair = Chip8::readRom("./roms/INVADERS");
    c8.loadRom(pair.first, pair.second);

//    c8.getDisplay().DrawSprite(0, 0, 0, 5, c8.getMemory());
//    c8.getDisplay().DrawSprite(10, 10, 5, 5, c8.getMemory());
//    c8.getDisplay().DrawSprite(20, 20, 10, 5, c8.getMemory());
//    c8.getDisplay().DrawSprite(30, 20, 15, 5, c8.getMemory());
//    c8.getDisplay().DrawSprite(40, 20, 20, 5, c8.getMemory());
//
//    c8.getRegisters().DelayTimer = 10;
//    c8.getRegisters().SoundTimer = 10;

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
        Update();
    }


    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
