#ifndef SNAKE_H
#define SNAKE_H
#include <cstdint>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

class Snake {
    public:
        enum class Direction {Up, Down, Left, Right};
        Snake(int32_t grid_width, int32_t grid_height);
        void update();
        void update_head();
        void update_body(SDL_Point &current_head, SDL_Point &previous_head);
        void grow_body();
        bool is_snakecell(int32_t x, int32_t y);
        const std::vector<SDL_Point>& get_body() const;
    private:
        bool m_Stopped;
        bool m_Growing;
        bool m_Alive;
        int32_t m_GridWidth;
        int32_t m_GridHeight;
        int32_t m_Size;
        float m_Speed;
        float m_HeadX;
        float m_HeadY;
        Direction m_Direction;
        std::vector<SDL_Point> m_Body;
        bool check_collision(SDL_Point &current_head);
};

#endif