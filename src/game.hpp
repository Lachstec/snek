#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <random>
#include <SDL2/SDL.h>
#include "sdl_exception.hpp"
#include "snake.hpp"


class Game {
    public:
        Game(int32_t width, int32_t height, int32_t grid_width, int32_t grid_height) noexcept(false);
        ~Game();
        void run();
    private:
        bool m_Running;
        const int32_t m_Width;
        const int32_t m_Height;
        const int32_t m_GridWidth;
        const int32_t m_GridHeight;
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        SDL_Point m_Food;
        Snake m_Snake;
        std::random_device m_Dev;
        std::mt19937 m_Gen;
        std::uniform_int_distribution<int32_t> m_Random_w;
        std::uniform_int_distribution<int32_t> m_Random_h;
        void draw();
        void generate_food();
};

#endif