#Server's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Game_Server)

# Set binary name
set(BINARY ${CMAKE_PROJECT_NAME})

# Set source folder
set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

# Set source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp)

# Set header file
set(HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h)

# Create executable BINARY
add_executable(${BINARY}_Server ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${BINARY}_Server PUBLIC ${ENET_PATH}/include)

target_link_libraries(${BINARY}_Server PUBLIC ${ENET_X64_WS2_WINM})
