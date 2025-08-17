cmake_minimum_required(VERSION 4.0)

project(
    Pong
    VERSION 1.0
    DESCRIPTION "Pong game made out of SDL, C++ and love"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
include_directories(/opt/homebrew/include/)
include_directories(include)
link_directories(/opt/homebrew/lib)

add_executable(pong src/main.cpp src/util.cpp)

target_link_libraries(pong SDL2 SDL2_ttf SDL2_mixer)