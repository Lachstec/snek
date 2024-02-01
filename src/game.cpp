#include "game.hpp"

Game::Game(int32_t width, int32_t height) noexcept(false)
    : m_Running(true), m_Width(width), m_Height(height)
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