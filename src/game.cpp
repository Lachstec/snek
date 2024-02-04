#include "game.hpp"

Game::Game(int32_t width, int32_t height, int32_t grid_width, int32_t grid_height) noexcept(false)
    : m_Running(true),
    m_Width(width),
    m_Height(height),
    m_GridWidth(grid_width),
    m_GridHeight(grid_height),
    m_Food(SDL_Point{ .x = 0, .y = 0}),
    m_Snake(Snake(grid_width, grid_height)),
    m_Dev(),
    m_Gen(m_Dev()),
    m_Random_w(0, static_cast<int32_t>(grid_width) - 1),
    m_Random_h(0, static_cast<int32_t>(grid_height) - 1)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SdlException(SDL_GetError());
    }
    m_Window = SDL_CreateWindow("snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, SDL_WINDOW_SHOWN);
    if(m_Window == nullptr) {
        throw SdlException(SDL_GetError());
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if(m_Renderer == nullptr) {
        throw SdlException(SDL_GetError());
    }
}

Game::~Game() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Game::generate_food() {
    int32_t x, y;
    while(true) {
        x = m_Random_w(m_Gen);
        y = m_Random_h(m_Gen);
        if(!m_Snake.is_snakecell(x, y)) {
            m_Food.x = x;
            m_Food.y = y;
            return;
        }
    }
}

void Game::draw() {
    SDL_Rect rectangle;
    rectangle.w = m_Width / m_GridWidth;
    rectangle.h = m_Height / m_GridHeight;

    // First, clear the screen
    SDL_SetRenderDrawColor(m_Renderer, 0x29, 0x31, 0x33, 0xFF);
    SDL_RenderClear(m_Renderer);

    // Draw the Fruit to eat
    SDL_SetRenderDrawColor(m_Renderer, 0xE0, 0x15, 0x0C, 0xFF);
    rectangle.x = m_Food.x * rectangle.w;
    rectangle.y = m_Food.y * rectangle.h;
    SDL_RenderFillRect(m_Renderer, &rectangle);

    // Draw Snake Body
    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for(auto const &point : m_Snake.get_body()) {
        rectangle.x = point.x * rectangle.w;
        rectangle.y = point.y * rectangle.h;
        SDL_RenderFillRect(m_Renderer, &rectangle);
    }

    // Draw Snake Head
    rectangle.x = static_cast<int32_t>(m_Snake.get_head_x());
    rectangle.y = static_cast<int32_t>(m_Snake.get_head_y());
    if(m_Snake.is_alive()) {
        SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(m_Renderer, &rectangle);
    SDL_RenderPresent(m_Renderer);
}

void Game::run() {

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    SDL_Rect rect;
    rect.x = 50;
    rect.y = 50;
    rect.h = 50;
    rect.w = 50;

    SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(m_Renderer, &rect);
    SDL_RenderPresent(m_Renderer);

    SDL_Event event;
    while(m_Running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    m_Running = false;
                    break;
                default:
                    continue;
            }
        }
    }
}