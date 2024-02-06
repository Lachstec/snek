#include "game.hpp"
#include <SDL_timer.h>
#include <cmath>

Game::Game(int32_t width, int32_t height, int32_t grid_width, int32_t grid_height) noexcept(false)
    : m_Running(true),
    m_Width(width),
    m_Height(height),
    m_GridWidth(grid_width),
    m_GridHeight(grid_height),
    m_Score(0),
    m_Food(SDL_Point{ .x = 0, .y = 0}),
    m_Snake(Snake(grid_width, grid_height)),
    m_FoodGen(Fruit(m_GridWidth, m_GridHeight, m_Snake))
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SdlException(SDL_GetError());
    }
    m_Window = SDL_CreateWindow("Snek --- Score: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, SDL_WINDOW_SHOWN);
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
    rectangle.x = static_cast<int32_t>(m_Snake.get_head_x()) * rectangle.w;
    rectangle.y = static_cast<int32_t>(m_Snake.get_head_y()) * rectangle.h;
    if(m_Snake.is_alive()) {
        SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(m_Renderer, &rectangle);
    SDL_RenderPresent(m_Renderer);
}

void Game::update() {
    if(!m_Snake.is_alive()) {
        return;
    }
    m_Snake.update();
    int32_t new_x = static_cast<int32_t>(m_Snake.get_head_x());
    int32_t new_y = static_cast<int32_t>(m_Snake.get_head_y());
    if(m_Food.x == new_x && m_Food.y == new_y) {
        m_Score += 1;
        m_FoodGen.generate_fruit(m_Food);
        m_Snake.grow_body();
        m_Snake.set_speed(m_Snake.get_speed() + 0.02);
    }
}

void Game::update_window_title() {
    std::string title {"Snek --- Score: " + std::to_string(m_Score)};
    SDL_SetWindowTitle(m_Window, title.c_str());
}

void Game::run() {
    Uint32 frame_start;
    Uint32 frame_end;

    while(m_Running) {

        frame_start = SDL_GetPerformanceCounter();

        m_Controller.handle_input(m_Running, m_Snake);
        update();
        draw();
        update_window_title();

        frame_end = SDL_GetPerformanceCounter();
        

        float elapsed = (frame_end - frame_start) / static_cast<float>(SDL_GetPerformanceFrequency());
        SDL_Delay(floor(16.666f - elapsed));
    }
}