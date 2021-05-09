cmake_minimum_required(VERSION 3.7)
project(SDL2Test)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/libSDL2.so)

find_package (SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(SDL2Test main.cpp)

target_link_libraries(SDL2Test ${SDL2_LIBRARY})