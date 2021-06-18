#Server's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files
set(server_lib Server_lib)
SOURCE_FILES(source_file_list src)
message(STATUS "[INFO] SERVER LIB ${server_lib} Found ${source_file_list_count} source files.")
add_library(${server_lib} ${source_file_list})

set(include_paths "${ENET_PATH}/include;${RENDERER_PATH}/libs/glm/glm;${Serializable_lib_include_path}")
message(STATUS "include_paths: ${include_paths}")
target_include_directories(${server_lib} PUBLIC ${include_paths})
target_link_libraries(${server_lib} PUBLIC ${ENET_X64_WS2_WINM}; k9_glm; Serializable_lib)

 message(STATUS "\nServer lib : ${server_lib}\n")

 set(Server_lib_include_path "${CMAKE_CURRENT_SOURCE_DIR}/src;${include_paths}" PARENT_SCOPE)
