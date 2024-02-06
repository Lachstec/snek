#include "fruit.hpp"

Fruit::Fruit(const int32_t grid_width, const int32_t grid_height, Snake &snake) 
    : m_Snake(snake),
    m_Dev(), 
    m_Gen(std::mt19937(m_Dev())), 
    m_Random_w(std::uniform_int_distribution(0, static_cast<int32_t>(grid_height) - 1)),
    m_Random_h(std::uniform_int_distribution(0, static_cast<int32_t>(grid_width) - 1))
{
    
}

void Fruit::generate_fruit(SDL_Point &fruit) {
    int32_t x, y;
    while(true) {
        x = m_Random_w(m_Gen);
        y = m_Random_h(m_Gen);
        if(!m_Snake.is_snakecell(x, y)) {
            fruit.x = x;
            fruit.y = y;
            return;
        }
    }
}