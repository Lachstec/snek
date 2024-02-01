#include <iostream>
#include <format>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << std::format("error initializing sdl2 context: {}\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << std::format("error creating window: {}\n", SDL_GetError());
        return -1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0F, 0xFF, 0x00));
    SDL_UpdateWindowSurface(window);

    bool exit = false;
    SDL_Event event;
    while(!exit) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    exit = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}