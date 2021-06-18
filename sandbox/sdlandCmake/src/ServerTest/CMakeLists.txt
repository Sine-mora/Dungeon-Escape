#ServerTEST's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set binary name
set(BINARY ${PROJECT_NAME}_ServerTest)

# Create executable BINARY
SOURCE_FILES(server_file_list src)
message(STATUS "[INFO] BLAAAAH SERVER ${BINARY} Found ${server_file_list} source files.")
add_executable(${BINARY} ${server_file_list})


# Това е CMake на ServerTest в папката sdlandCmake/src/ServerTest
target_include_directories(${BINARY} PUBLIC K9_Renderer_include_list)
target_link_libraries(${BINARY} PUBLIC K9_Renderer) 

set(SERVER_LIB_PATH ${LIBS}/Server)
add_subdirectory(${SERVER_LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libs/Server)
message(STATUS "Server_lib_include_path: ${Server_lib_include_path}")
target_include_directories(${BINARY} PUBLIC ${Server_lib_include_path})

set(SOL_PATH ${LIBS}/sol)
target_include_directories(${BINARY} PUBLIC ${SOL_PATH})

set(LUA_PATH ${LIBS}/lua)
target_include_directories(${BINARY} PUBLIC ${LUA_PATH}/include)


target_link_libraries(${BINARY} PUBLIC Server_lib; K9_Renderer; lua_lib)
