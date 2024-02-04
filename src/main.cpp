#include <iostream>
#include "game.hpp"
#include "sdl_exception.hpp"

int main() {
    try {
        Game game(640, 640, 32, 32);
        game.run();
    } catch(const SdlException& ex) {
        std::cerr << "error initializing game: " << ex.what() << "\n";
        return -1;
    }
    return 0;
}