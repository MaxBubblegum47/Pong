cmake_minimum_required(VERSION 4.0)

project(
    Pong
    VERSION 1.0
    DESCRIPTION "Pong game made out of SDL, C++ and love"
    LANGUAGES CXX)

include_directories(/opt/homebrew/include/)
link_directories(/opt/homebrew/lib)

add_executable(pong main.cpp)

target_link_libraries(pong SDL2 SDL2_ttf)