#Client's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp)
    
# Set header file
set(HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.h)

set(client_lib ${BINARY}_lib)

add_library(${client_lib} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${client_lib} PUBLIC ${ENET_PATH}/include; ${GLM_PATH}/include)

target_link_libraries(${client_lib} PUBLIC ${ENET_X64_WS2_WINM}; glm)

 message(STATUS "\nClient lib : ${client_lib}\n")