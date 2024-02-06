#pragma once
#include <cstdint>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

enum class Direction {Up, Down, Left, Right};

class Snake {
    public:
        Snake(int32_t grid_width, int32_t grid_height);
        void update();
        void grow_body();
        bool is_snakecell(int32_t x, int32_t y) const;
        bool is_alive() const;
        const std::vector<SDL_Point>& get_body() const;
        const float& get_head_x() const;
        const float& get_head_y() const;
        const int32_t& get_size() const;
        const float& get_speed() const;
        void set_speed(float new_speed);
        Direction m_Direction;
    private:
        bool m_Growing, m_Alive;
        int32_t m_GridWidth, m_GridHeight, m_Size;
        float m_Speed, m_HeadX, m_HeadY;
        std::vector<SDL_Point> m_Body;
        bool check_collision(SDL_Point &current_head);
        void update_head();
        void update_body(SDL_Point &current_head, SDL_Point &previous_head);
};