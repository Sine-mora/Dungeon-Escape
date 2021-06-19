cmake_minimum_required(VERSION 3.1)

project(Dungeon-Escape)

message(STATUS "${PROJECT_NAME} is located in ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify C++17 as the standard
set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 17)

message(STATUS "CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

message(STATUS "====== Current compiler is: ${CMAKE_CXX_COMPILER} ======")
message(STATUS "====================================")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    message(STATUS "No selected build type")
    message(STATUS "Setting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
else()
    message(STATUS "Selected build type is ${CMAKE_BUILD_TYPE}")
endif()
message(STATUS "====================================")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/k9/examples/ImGui_Example/Renderer)

set(BINARY ${PROJECT_NAME})
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

SOURCE_FILES(source_file_list src)
list(LENGTH source_file_list source_file_list_count)
message(STATUS "[INFO] ${BINARY} Found ${source_file_list_count} source files.")
add_executable(${BINARY} ${source_file_list})

target_link_libraries(${BINARY} PUBLIC K9_Renderer)
target_include_directories(${BINARY} PUBLIC
							${CMAKE_CURRENT_SOURCE_DIR}/src
							${CMAKE_CURRENT_SOURCE_DIR}/src/Components
							${LIBS}
							K9_Renderer_include_list)


#todo erase when k9 is fully integrated
    set(SDL_PATH ${LIBS}/SDL2)
	    add_subdirectory(${SDL_PATH})

set(LUA_PATH ${LIBS}/lua)
add_subdirectory(${LUA_PATH})
target_include_directories(${BINARY} PUBLIC ${LUA_INCLUDE_DIRS})
	
set(SOL_PATH ${LIBS}/sol)
add_subdirectory(${SOL_PATH})
target_include_directories(${BINARY} PUBLIC ${SOL_PATH})

target_link_libraries(${BINARY} PUBLIC ${SDL2_LIBRARIES}; lua_lib;)


copy_assets("${BINARY}"
			"${BINARY}_assets"
			"${K9_ASSET_COPY_SCRIPT_PATH}"
			"${CMAKE_CURRENT_SOURCE_DIR}/assets"
			"${CMAKE_CURRENT_BINARY_DIR}")

copy_asset_list("${BINARY}"
				"${BINARY}_lua"
				"${K9_LIB_COPY_SCRIPT_PATH}"
				"${LUA_PATH}/lua53.dll"
				"${CMAKE_CURRENT_BINARY_DIR}")
 
copy_assets("${K9_ASSET_TARGET}"
			"${K9_ASSET_DEPENDENCY}"
			"${K9_ASSET_COPY_SCRIPT_PATH}"
			"${K9_ASSET_FOLDER_TO_COPY}"
			"${CMAKE_CURRENT_BINARY_DIR}")
message(status "Client K9_LIBS_TO_COPY: ${K9_LIBS_TO_COPY}")
copy_asset_list("${K9_LIB_TARGET}"
			"${K9_LIB_DEPENDENCY}"
			"${K9_LIB_COPY_SCRIPT_PATH}"
			"${K9_LIBS_TO_COPY}"
			"${CMAKE_CURRENT_BINARY_DIR}")