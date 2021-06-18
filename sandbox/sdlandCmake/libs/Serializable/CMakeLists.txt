#Serializable Cmake
cmake_minimum_required(VERSION 3.7.2)

# Specify C++14 as the standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 17)


# Add library Serializable
SOURCE_FILES(source_file_list src)
add_library(Serializable_lib ${source_file_list})

#Set include path
set(Serializable_lib_include_path ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)