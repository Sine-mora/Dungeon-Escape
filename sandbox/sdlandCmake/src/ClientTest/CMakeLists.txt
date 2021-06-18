# Това е CMake на ClientTest в папката sdlandCmake/src/ClientTest    
cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set binary name
set(BINARY ${PROJECT_NAME}_ClientTest)

SOURCE_FILES(source_file_list src)
add_executable(${BINARY} ${source_file_list})

list(LENGTH source_file_list source_file_list_count)
message(STATUS "[INFO] ${BINARY} Found ${source_file_list_count} source files.")

if(WIN32)
    target_include_directories(${BINARY} PUBLIC K9_Renderer_include_list)
    target_link_libraries(${BINARY} PUBLIC K9_Renderer) 

   set(CLIENT_LIB_PATH ${LIBS}/Client)
        add_subdirectory(${CLIENT_LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libs/Client)
        target_include_directories(${BINARY} PUBLIC ${Client_lib_include_path})

    set(SOL_PATH ${LIBS}/sol)
	   target_include_directories(${BINARY} PUBLIC ${SOL_PATH})

    set(LUA_PATH ${LIBS}/lua)
        target_include_directories(${BINARY} PUBLIC ${LUA_PATH}/include)

        target_link_libraries(${BINARY} PUBLIC Client_lib; ${ENET_X64_WS2_WINM}; lua_lib)



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