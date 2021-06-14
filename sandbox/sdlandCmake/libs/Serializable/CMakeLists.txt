cmake_minimum_required(VERSION 3.7.2)

# Specify C++14 as the standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 14)

MACRO(HEADER_DIRECTORIES return_list curr_dir)
    FILE(GLOB_RECURSE new_list ${curr_dir}/*.h ${curr_dir}/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

MACRO(SOURCE_FILES return_list curr_dir)
    FILE(GLOB_RECURSE new_list ${curr_dir}/*.h ${curr_dir}/*.cpp ${curr_dir}/*.hpp ${curr_dir}/*.inl ${curr_dir}/*.c)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        message(STATUS "[INFO] file_path: ${file_path}")
        SET(dir_list ${dir_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

SOURCE_FILES(source_file_list src)

list(LENGTH source_file_list source_file_list_count)

# Add library Serializable
set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SERIALIZABLE_SOURCES ${SRC_PATH}/Serializable.h      # ${SOURCE_FILES} ${HEADER DIRECTORIES}
                                ${SRC_PATH}/Serializable.cpp
                                ${SRC_PATH}/Person.h
                                ${SRC_PATH}/Person.cpp
                                ${SRC_PATH}/Point.h
                                ${SRC_PATH}/Point.cpp)
message(STATUS "lib src: ${SRC_PATH} : sources: ${SERIALIZABLE_SOURCES}")

add_library(Serializable ${SERIALIZABLE_SOURCES})