#Main Cmake in sdlandCmake/Cmake.txt
cmake_minimum_required(VERSION 3.2)

project(SDL_Test)

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

set(IMGUI_EXAMPLE_PATH ../../libs/k9/examples/ImGui_Example)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

#Add Renderer
add_subdirectory(${IMGUI_EXAMPLE_PATH}/Renderer ${CMAKE_CURRENT_SOURCE_DIR}/Renderer)

#Add ENet
    set(ENET_PATH ${LIBS}/enet)
     #ENet needed libs for Windows
    set(ENET_LIB "${ENET_PATH}/lib/x64/enet")
    set(ENET_X64_WS2_WINM "${ENET_LIB};ws2_32.lib;winmm.lib")
    add_subdirectory(${LIBS}/enet)

#Add ClientTest and Client_lib
    add_subdirectory(${SRC_DIR}/ClientTest)
    add_subdirectory(${LIBS}/Client)
    
#Add ServerTest and Server_lib
    add_subdirectory(${SRC_DIR}/ServerTest)
set(SERVER_PATH ${LIBS}/Server)  
    add_subdirectory(${SERVER_PATH})

#Add Serializable/Point/Person
    add_subdirectory(${LIBS}/Serializable)

#Add Lua
    add_subdirectory(${LIBS}/lua)

#Add Sol
    add_subdirectory(${LIBS}/sol)


copy_assets("${K9_LIB_ASSET_TARGET}"
			"${K9_LIB_ASSET_DEPENDENCY}"
			"${K9_LIB_ASSET_COPY_SCRIPT_PATH}"
			"${K9_LIB_ASSET_FOLDER_TO_COPY}"
			"${CMAKE_CURRENT_BINARY_DIR}")

# Set the exe path for the K9_renderer
set(EXE_PATH ${CMAKE_CURRENT_BINARY_DIR})