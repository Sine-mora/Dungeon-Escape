add_library(SDL2_LIBRARY STATIC SDL2.dll SDL2.lib)
target_include_directories(SDL2_LIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../../include)