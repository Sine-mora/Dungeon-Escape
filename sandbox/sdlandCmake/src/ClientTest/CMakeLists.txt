# Това е CMake на ClientTest в папката sdlandCmake/src/ClientTest    
cmake_minimum_required(VERSION 3.2)

#Set binary name
set(BINARY ${PROJECT_NAME}_ClientTest)

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

function(post_build_copy argFileToCopy)
    message(STATUS "[INFO]\n\n\n post_build_copy  ${PROJECT_NAME} \n\t\t copying argFileToCopy: ${argFileToCopy}\n\t\t to CMAKE_CURRENT_BINARY_DIR:  ${CMAKE_CURRENT_BINARY_DIR}\n")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different           
        ${argFileToCopy}                                    
        ${CMAKE_CURRENT_BINARY_DIR})                        
endfunction()

set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${LIBS}/Client/Client.cpp)

set(HEADER_FILES
    ${LIBS}/Client/Client.h)

add_executable(${BINARY} ${HEADER_FILES} ${SRC_FILES})

list(LENGTH source_file_list source_file_list_count)
message(STATUS "[INFO] ${BINARY} Found ${source_file_list_count} source files.")

set(LIBS ../../libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${LIBS})

if(UNIX)
    find_package(SDL2 REQUIRED)
    target_link_libraries(${BINARY} PUBLIC SDL2)
endif(UNIX)
if(WIN32)   
   
     set(RENDERER_PATH ../../../../libs/k9/examples/ImGui_Example/Renderer/)
    
    target_include_directories(${BINARY} PUBLIC K9_Renderer_include_list)
    target_link_libraries(${BINARY} PUBLIC K9_Renderer) 

   set(CLIENT_LIB_PATH ${LIBS}/Client)
        add_subdirectory(${CLIENT_LIB_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Client)
        target_include_directories(${BINARY} PUBLIC ${CLIENT_LIB_PATH})

    set(SERIALIZABLE_PATH ${LIBS}/Serializable/src)
        target_include_directories(${BINARY} PUBLIC ${SERIALIZABLE_PATH})

    set(ENET_PATH ${LIBS}/enet)
     #ENet needed libs for Windows
    set(ENET_LIB "${ENET_PATH}/lib/x64/enet")
    set(ENET_X64_WS2_WINM "${ENET_LIB};ws2_32.lib;winmm.lib")
        target_include_directories(${BINARY} PUBLIC ${ENET_PATH}/include)

    set(SOL_PATH ${LIBS}/sol)
	   target_include_directories(${BINARY} PUBLIC ${SOL_PATH})

    set(LUA_PATH ${LIBS}/lua)
        target_include_directories(${BINARY} PUBLIC ${LUA_PATH}/include)

        target_link_libraries(${BINARY} PUBLIC ${ENET_X64_WS2_WINM}; lua_lib)



    message(STATUS "[INFO] ${BINARY}_Client SDL_PATH: ${SDL_PATH}\n SDL_INCLUDE_DIRS:  ${SDL2_INCLUDE_DIRS} \n SDL2_LIBRARIES: ${SDL2_LIBRARIES} \n EXTERN_SDL_LIBS_PATH: ${EXTERN_SDL_LIBS_PATH} \n
SDL_IMAGE_PATH: ${SDL_IMAGE_PATH}\n SDL_IMAGE_INCLUDE_DIRS: ${SDL2_IMAGE_INCLUDE_DIRS} \n SDL2_IMAGE_LIBRARIES: ${SDL2_IMAGE_LIBRARIES} \n EXTERN_SDL_IMAGE_PATH: ${EXTERN_SDL_IMAGE_LIBS_PATH} \n
SDL_MIXER_PATH: ${SDL_MIXER_PATH}\n SDL_MIXER_INCLUDE_DIRS: ${SDL2_MIXER_INCLUDE_DIRS} \n SDL2_MIXER_LIBRARIES: ${SDL2_MIXER_LIBRARIES} \n EXTERN_SDL_MIXER_PATH: ${EXTERN_SDL_MIXER_LIBS_PATH} \n
SDL_TTF_PATH: ${SDL_TTF_PATH}\n SDL_TTF_INCLUDE_DIRS: ${SDL2_TTF_INCLUDE_DIRS} \n SDL2_TTF_LIBRARIES: ${SDL2_TTF_LIBRARIES} \n EXTERN_SDL_TTF_PATH: ${EXTERN_SDL_TTF_LIBS_PATH} \n
[include Dir of LUA]: ${LUA_INCLUDE_DIRS}\n ENET_PATH: ${ENET_PATH} \n ENET_LIB: ${ENET_LIB} \n client_lib: ${client_lib}")

endif(WIN32)

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