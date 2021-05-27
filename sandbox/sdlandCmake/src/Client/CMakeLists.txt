#Client's Cmake
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Game_Client)

#include_directories()

# Set binary name
set(BINARY ${CMAKE_PROJECT_NAME})

# Set source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp)
    
# Set header file
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Client.h)

# Create executable BINARY
add_executable(${BINARY} ${HEADER_FILES} ${SOURCE_FILES})

set(ENET_PATH ../../libs/enet)
        include_directories(ENET_PATH)
        set(ENET_LIB "${ENET_PATH}/lib/x64/enet.lib")
        set(ENET_X64_WS2_WINM "${ENET_LIB};ws2_32.lib;winmm.lib")
        add_subdirectory(${ENET_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/build)
        target_include_directories(${BINARY} PUBLIC ${ENET_PATH}/include)

 target_link_libraries(${BINARY} PUBLIC ${ENET_X64_WS2_WINM})