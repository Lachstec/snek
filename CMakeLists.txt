cmake_minimum_required(VERSION 3.27)

project(snek
    VERSION 0.1.0
    DESCRIPTION "small snek game"
    LANGUAGES CXX
)

add_executable(snek
    src/main.cpp
)

target_compile_features(snek PRIVATE cxx_std_23)
target_compile_options(snek PRIVATE -Wall -Wextra -Wpedantic)