#pragma once
#include <SDL2/SDL.h>
#include "snake.hpp"

class Controller {
    public:
        void handle_input(bool &running, Snake &snake) const;
    private:
        void change_direction(Snake &snake, Direction direction, Direction opposite) const;
};