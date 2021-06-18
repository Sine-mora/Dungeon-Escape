#Main Cmake in sdlandCmake/Cmake.txt
cmake_minimum_required(VERSION 3.7.2)

project(SDL_Test)

set(RENDERER_PATH ../../libs/k9/examples/ImGui_Example/Renderer)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

#Add Renderer
message(STATUS "RENDERER_PATH = ${RENDERER_PATH}")
add_subdirectory(${RENDERER_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libs/k9/Renderer)

#Add ENet
set(ENET_PATH ${LIBS}/enet)
 #ENet needed libs for Windows
set(ENET_LIB "${ENET_PATH}/lib/x64/enet")
set(ENET_X64_WS2_WINM "${ENET_LIB};ws2_32.lib;winmm.lib")
add_subdirectory(${LIBS}/enet)


#Add Sol
add_subdirectory(${LIBS}/sol)

#Add Lua
add_subdirectory(${LIBS}/lua)

#Add Serializable/Point/Person
add_subdirectory(${LIBS}/Serializable)

#Add ClientTest and Client_lib
add_subdirectory(${SRC_DIR}/ClientTest)
    
#Add ServerTest and Server_lib
add_subdirectory(${SRC_DIR}/ServerTest)


copy_assets("${K9_LIB_ASSET_TARGET}"
			"${K9_LIB_ASSET_DEPENDENCY}"
			"${K9_LIB_ASSET_COPY_SCRIPT_PATH}"
			"${K9_LIB_ASSET_FOLDER_TO_COPY}"
			"${CMAKE_CURRENT_BINARY_DIR}")