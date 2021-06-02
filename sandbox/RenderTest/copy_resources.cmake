cmake_minimum_required(VERSION 3.7.2)
message(STATUS "copy_resources.cmake : source: ${CMAKE_CURRENT_LIST_DIR}/assets target:  ${ASSETS_PATH}")
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${ASSETS_PATH})