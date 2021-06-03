cmake_minimum_required(VERSION 3.7.2)

# Name of the project
project(ImGUI_Example)

message(STATUS "${PROJECT_NAME} is located in ${CMAKE_CURRENT_SOURCE_DIR}")

# Specify C++17 as the standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
set(EXE_PATH ${CMAKE_CURRENT_BINARY_DIR})


# Output compiler Information and build type
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

# Name of the executable
set(BINARY ${PROJECT_NAME})

# Get all source files and headers in src/
add_subdirectory(../../libs/k9/examples/ImGui_Example/Renderer ${CMAKE_CURRENT_SOURCE_DIR}/dirs/Renderer)
SOURCE_FILES(source_file_list src)

list(LENGTH source_file_list source_file_list_count)
message(STATUS "[INFO] ${BINARY} Found ${source_file_list_count} source files.")

# Create BINARY executable
add_executable(${BINARY} ${source_file_list})

# Add include directories

target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src K9_Renderer_include_list)
target_link_libraries(${BINARY} PUBLIC K9_Renderer)

 copy_assets("${BINARY}" "${BINARY}_assets" "${CMAKE_CURRENT_SOURCE_DIR}/copy_resources.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/assets")

#Copy the Assets folder
#   set(ASSETS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets)
#  file(COPY ${ASSETS_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	#End of copy