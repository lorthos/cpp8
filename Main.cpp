#include <SDL.h>
#include <SDL_system.h>


SDL_Window *mWindow;
SDL_Renderer *mRenderer;

bool InitializeWindow(int xres, int yres) {


    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    mWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               xres,
                               yres,
                               SDL_WINDOW_SHOWN |
                               SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);


    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Draw() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);
}

int main(int argc, char **argv) {
    int x = 640;
    int y = 320;
    InitializeWindow(x, y);
    bool mIsRunning = true;

    while (mIsRunning) {
        // process input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    mIsRunning = false;
                    break;
                case SDL_KEYDOWN:
                    mIsRunning = false;
                    break;
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
