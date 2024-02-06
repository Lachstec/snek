cmake_minimum_required(VERSION 3.27)

# Project Specification
project(snek
    VERSION 0.1.0
    DESCRIPTION "small snek game"
    LANGUAGES CXX
)

# SDL2 as Dependency for Graphics
find_package(SDL2 REQUIRED)

# Add SDL2 Include Files to Include Search Path
include_directories(${SDL2_INCLUDE_DIRS})

# Add source files to project
add_executable(snek
    src/main.cpp
    src/game.cpp
    src/sdl_exception.cpp
    src/snake.cpp
    src/controller.cpp
    src/fruit.cpp
)

target_compile_features(snek PRIVATE cxx_std_23)
target_compile_options(snek PRIVATE -Wall -Wextra -Wpedantic)

# Link SDL2 Libraries
target_link_libraries(snek ${SDL2_LIBRARIES})