cmake_minimum_required(VERSION 3.7.2)
# ASSETS_SOURCE_DIR - directory to be copied
# ASSETS_OUTPUT_DIR - specifies where the directory will be copied
message(STATUS "copy_resources.cmake : source: ${ASSETS_SOURCE_DIR} output:  ${ASSETS_OUTPUT_DIR}")
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_OUTPUT_DIR})