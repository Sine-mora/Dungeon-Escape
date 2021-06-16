#Server's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set binary name
set(BINARY ${PROJECT_NAME}_ServerTest)

# Set source folder
set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS ../../libs)

# Set source files
set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${LIBS}/Server/Server.cpp)

# Set header file
set(HEADER_FILES 
    ${LIBS}/Server/Server.h)

# Create executable BINARY
add_executable(${BINARY} ${HEADER_FILES} ${SRC_FILES})

# Това е CMake на ServerTest в папката sdlandCmake/src/ServerTest    
     set(RENDERER_PATH ../../../../libs/k9/examples/ImGui_Example/Renderer/)
    
    target_include_directories(${BINARY} PUBLIC K9_Renderer_include_list)
    target_link_libraries(${BINARY} PUBLIC K9_Renderer) 

target_include_directories(${BINARY} PUBLIC ${ENET_PATH}/include ${LIBS}/Serializable/src)
target_link_libraries(${BINARY} PUBLIC ${ENET_X64_WS2_WINM}; K9_Renderer)
