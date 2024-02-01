#include <iostream>
#include <format>
#include "game.hpp"
#include "sdl_exception.hpp"

int main() {
    try {
        Game game(640, 480);
        game.run();
    } catch(const SdlException& ex) {
        std::cerr << std::format("error initializing game: {}\n", ex.what());
        return -1;
    }
    return 0;
}