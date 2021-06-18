#Client's Cmake
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(client_lib Client_lib)
SOURCE_FILES(source_file_list src)
message(STATUS "[INFO] BLAAAAAH ${client_lib} Found ${source_file_list_count} source files.")
add_library(${client_lib} ${source_file_list})

set(include_paths "${ENET_PATH}/include;${RENDERER_PATH}/libs/glm/glm;${Serializable_lib_include_path}")
message(STATUS "include_paths: ${include_paths}")
target_include_directories(${client_lib} PUBLIC ${include_paths})
target_link_libraries(${client_lib} PUBLIC ${ENET_X64_WS2_WINM}; k9_glm; Serializable_lib)

 message(STATUS "\nClient lib : ${client_lib}\n")
set(Client_lib_include_path "${CMAKE_CURRENT_SOURCE_DIR}/src;${include_paths}" PARENT_SCOPE)
