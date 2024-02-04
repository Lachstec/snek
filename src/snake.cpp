#include "snake.hpp"

Snake::Snake(int32_t grid_width, int32_t grid_height)
    : m_Stopped(true),
    m_Growing(false),
    m_Alive(true),
    m_GridWidth(grid_width),
    m_GridHeight(grid_height),
    m_Size(1),
    m_Speed(0.1f),
    m_HeadX(static_cast<float>(grid_width) / 2),
    m_HeadY(static_cast<float>(grid_height) / 2),
    m_Direction(Direction::Up)
{

}

void Snake::update() {
    SDL_Point previous_pos {
        static_cast<int>(m_HeadX),
        static_cast<int>(m_HeadY)
    };
    update_head();
    SDL_Point current_pos {
        static_cast<int>(m_HeadX),
        static_cast<int>(m_HeadY),
    };

    if(current_pos.x != previous_pos.x || current_pos.y != previous_pos.y) {
        update_body(current_pos, previous_pos);
    }
}

void Snake::update_head() {
    if(!m_Stopped) {
        switch(m_Direction) {
            case Direction::Up:
                m_HeadY -= m_Speed;
                break;

            case Direction::Down:
                m_HeadY += m_Speed;
                break;
            
            case Direction::Left:
                m_HeadX -= m_Speed;
                break;

            case Direction::Right:
                m_HeadX += m_Speed;
                break;
        }

        // Wrap the Snake around if coordinates should exceed the grid size
        m_HeadX = std::fmod(m_HeadX + m_GridWidth, m_GridWidth);
        m_HeadY = std::fmod(m_HeadY + m_GridHeight, m_GridHeight);
    }
}

void Snake::update_body(SDL_Point &current_head, SDL_Point &previous_head) {
    m_Body.push_back(previous_head);

    if(!m_Growing) {
        m_Body.erase(m_Body.begin());
    } else {
        m_Growing = false;
        m_Size += 1;
    }

    if(check_collision(current_head)) {
        m_Alive = false;
    }
}

void Snake::grow_body() {
    m_Growing = true;
}

bool Snake::check_collision(SDL_Point &current_head) {
    for(auto const &part: m_Body) {
        if(current_head.x == part.x && current_head.y == part.y) {
            return true;
        }
    }
    return false;
}

bool Snake::is_snakecell(int32_t x, int32_t y) {
    if(x == static_cast<int32_t>(m_HeadX) && y == static_cast<int32_t>(m_HeadY)) {
        return true;
    }

    for(auto const &item : m_Body) {
        if(x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}