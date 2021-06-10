cmake_minimum_required(VERSION 3.7.2)

# Specify C++14 as the standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 14)

# Add library Serializable
set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SERIALIZABLE_SOURCES ${SRC_PATH}/Serializable.h
                                ${SRC_PATH}/Serializable.cpp
                                ${SRC_PATH}/Person.h
                                ${SRC_PATH}/Person.cpp)
message(STATUS "lib src: ${SRC_PATH} : sources: ${SERIALIZABLE_SOURCES}")

add_library(Serializable ${SERIALIZABLE_SOURCES} "src/Point.cpp" "src/Point.h")