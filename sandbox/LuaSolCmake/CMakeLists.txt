cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(helloLua VERSION 1.0)


find_file(Lua_INCLUDE_DIR NAME lua.h HINTS lua)
find_library(Lua_LIBRARY NAME lua)

add_subdirectory(libs/luaAndSol)

add_executable(helloLua main.cpp)
include_directories(helloLua PUBLIC libs/luaAndSol)  
target_link_libraries(helloLua PUBLIC ${Lua_LIBRARY})



#target_include_directories(helloLua PUBLIC ${LUA_INCLUDE_DIR})
#target_link_libraries(helloLua PUBLIC lua_lib ${LUA_LIBRARIES} ${LUA_DEPENDENCIES})


# file(GLOB_RECURSE SRC_FILES src/*.cpp) #Loops through all .cpp files and adds them to a variable #
# add_executable(hello ${SRC_FILES} ) # Add source files to project (main.cpp src/Blah.cpp) #
# target_include_directories(helloLua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # Include files from a specified dir to executable #
