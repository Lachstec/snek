#pragma once
#include <random>
#include <SDL2/SDL.h>
#include "snake.hpp"

class Fruit {
    public:
        Fruit(const int32_t grid_width, const int32_t grid_height, Snake &snake);
        void generate_fruit(SDL_Point &fruit);
    private:
        Snake &m_Snake;
        std::random_device m_Dev;
        std::mt19937 m_Gen;
        std::uniform_int_distribution<int32_t> m_Random_w;
        std::uniform_int_distribution<int32_t> m_Random_h;
};