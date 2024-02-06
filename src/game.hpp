#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <random>
#include <string>
#include <SDL2/SDL.h>
#include "sdl_exception.hpp"
#include "snake.hpp"
#include "controller.hpp"
#include "fruit.hpp"


class Game {
    public:
        Game(int32_t width, int32_t height, int32_t grid_width, int32_t grid_height) noexcept(false);
        ~Game();
        void run();
    private:
        bool m_Running;
        const int32_t m_Width, m_Height, m_GridWidth, m_GridHeight;
        int32_t m_Score;
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        SDL_Point m_Food;
        Snake m_Snake;
        Fruit m_FoodGen;
        Controller m_Controller;
        void draw();
        void update();
        void update_window_title();
};

#endif