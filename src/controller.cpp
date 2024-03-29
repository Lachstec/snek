#include "controller.hpp"

void Controller::handle_input(bool &running, Snake &snake) const {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
        } else if( event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    change_direction(snake, Direction::Up, Direction::Down);
                    break;
                case SDLK_DOWN:
                    change_direction(snake, Direction::Down, Direction::Up);
                    break;
                case SDLK_LEFT:
                    change_direction(snake, Direction::Left, Direction::Right);
                    break;
                case SDLK_RIGHT:
                    change_direction(snake, Direction::Right, Direction::Left);
                    break;
            }
        }
    }
}

void Controller::change_direction(Snake &snake, Direction direction, Direction opposite) const {
    if(snake.m_Direction != opposite || snake.get_size() == 1) {
        snake.m_Direction = direction;
    }
}