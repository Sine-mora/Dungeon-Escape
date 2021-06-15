cmake_minimum_required(VERSION 3.2)

project(SDL_Test)

message(STATUS "${PROJECT_NAME} is located in ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

function(post_build_copy argFileToCopy)
    message(STATUS "[INFO]\n\n\n post_build_copy  ${PROJECT_NAME} \n\t\t copying argFileToCopy: ${argFileToCopy}\n\t\t to CMAKE_CURRENT_BINARY_DIR:  ${CMAKE_CURRENT_BINARY_DIR}\n")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different           
        ${argFileToCopy}                                    
        ${CMAKE_CURRENT_BINARY_DIR})                        
endfunction()

set(BINARY ${PROJECT_NAME})

SOURCE_FILES(source_file_list src)

list(LENGTH source_file_list source_file_list_count)
message(STATUS "[INFO] ${BINARY} Found ${source_file_list_count} source files.")

add_executable(${BINARY} ${source_file_list})

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${LIBS})

  set(IMGUI_EXAMPLE_PATH ../../libs/k9/examples/ImGui_Example/Renderer)
  message(STATUS "[INFO] IMGUI_EXAMPLE_PATH: ${IMGUI_EXAMPLE_PATH}")

if(UNIX)
    find_package(SDL2 REQUIRED)
    target_link_libraries(${BINARY} PUBLIC SDL2)
endif(UNIX)
if(WIN32)
	
    set(GLM_PATH ${IMGUI_EXAMPLE_PATH}/libs/glm)
        add_subdirectory(${GLM_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/dirs/glm)
	    target_include_directories(${BINARY} PUBLIC ${GLM_PATH})
	
    set(IMGUI_PATH ${IMGUI_EXAMPLE_PATH}/libs/imgui)
        add_subdirectory(${IMGUI_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/dirs/imgui)
	    target_include_directories(${BINARY} PUBLIC ${IMGUI_PATH})

    set(SERIALIZEABLE_PATH ${LIBS}/Serializable)
        add_subdirectory(${SERIALIZEABLE_PATH})
        target_include_directories(${BINARY} PUBLIC ${SERIALIZEABLE_PATH}/src)


	
    target_link_libraries(${BINARY} PUBLIC imgui; glm; Serializable)

    message(STATUS "[INFO] ${BINARY} SDL_PATH: ${SDL_PATH}\n SDL_INCLUDE_DIRS:  ${SDL2_INCLUDE_DIRS} \n SDL2_LIBRARIES: ${SDL2_LIBRARIES} \n EXTERN_SDL_LIBS_PATH: ${EXTERN_SDL_LIBS_PATH} \n
SDL_IMAGE_PATH: ${SDL_IMAGE_PATH}\n SDL_IMAGE_INCLUDE_DIRS: ${SDL2_IMAGE_INCLUDE_DIRS} \n SDL2_IMAGE_LIBRARIES: ${SDL2_IMAGE_LIBRARIES} \n EXTERN_SDL_IMAGE_PATH: ${EXTERN_SDL_IMAGE_LIBS_PATH} \n
SDL_MIXER_PATH: ${SDL_MIXER_PATH}\n SDL_MIXER_INCLUDE_DIRS: ${SDL2_MIXER_INCLUDE_DIRS} \n SDL2_MIXER_LIBRARIES: ${SDL2_MIXER_LIBRARIES} \n EXTERN_SDL_MIXER_PATH: ${EXTERN_SDL_MIXER_LIBS_PATH} \n
SDL_TTF_PATH: ${SDL_TTF_PATH}\n SDL_TTF_INCLUDE_DIRS: ${SDL2_TTF_INCLUDE_DIRS} \n SDL2_TTF_LIBRARIES: ${SDL2_TTF_LIBRARIES} \n EXTERN_SDL_TTF_PATH: ${EXTERN_SDL_TTF_LIBS_PATH} \n
[include Dir of LUA]: ${LUA_INCLUDE_DIRS}\n ENET_PATH: ${ENET_PATH} \n ENET_LIB: ${ENET_LIB} \n client_lib: ${client_lib}")

endif(WIN32)