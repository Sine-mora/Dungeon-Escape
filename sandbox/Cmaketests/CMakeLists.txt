cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello VERSION 1.0)


find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

add_subdirectory(libs/SDL2-2.0.14/lib/x86)

add_executable(hello main.cpp)
include_directories(hello PUBLIC libs/SDL2-2.0.14/lib/x86)  
target_link_libraries(hello PUBLIC ${SDL2_LIBRARY})














#target_include_directories(hello PUBLIC ${SDL_INCLUDE_DIR})
#target_link_libraries(hello PUBLIC blah ${SDL_LIBRARIES} ${SDL_DEPENDENCIES})


# file(GLOB_RECURSE SRC_FILES src/*.cpp) #Loops through all .cpp files and adds them to a variable #
# add_executable(hello ${SRC_FILES} ) # Add source files to project (main.cpp src/Blah.cpp) #
# target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # Include files from a specified dir to executable #
