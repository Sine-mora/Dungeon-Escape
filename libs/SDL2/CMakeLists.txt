set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include" PARENT_SCOPE)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x64")
else ()
  set(SDL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x86")
endif ()

# Set the SDL_LIBS_PATH variable to be used in the parent CMakeLists.txt scope
set(EXTERN_SDL_LIBS_PATH ${SDL_LIBS_PATH} PARENT_SCOPE)

# Set the static libraries paths for the parent scope
set(SDL2_LIBRARIES "${SDL_LIBS_PATH}/SDL2.lib;${SDL_LIBS_PATH}/SDL2main.lib" PARENT_SCOPE)

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

# Parent Scope за да може да се използват в горния Смейк