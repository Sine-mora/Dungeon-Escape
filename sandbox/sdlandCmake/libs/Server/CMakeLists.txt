#Server's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp)
    
# Set header file
set(HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h)

set(server_lib ${BINARY}_Server_lib)

add_library(${server_lib} ${SOURCE_FILES} ${HEADER_FILES})

#IMGUI_EXAMPLE_PATH

target_include_directories(${server_lib} PUBLIC ${ENET_PATH}/include; ${GLM_PATH}/include)

target_link_libraries(${server_lib} PUBLIC ${ENET_X64_WS2_WINM}; glm)

 message(STATUS "\nServer lib : ${server_lib}\n")

