#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <SDL2/SDL.h>
#include "sdl_exception.hpp"


class Game {
    public:
        Game(int32_t width, int32_t height) noexcept(false);
        ~Game();
        void run();
    private:
        bool m_Running;
        const int32_t m_Width;
        const int32_t m_Height;
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
};

#endif