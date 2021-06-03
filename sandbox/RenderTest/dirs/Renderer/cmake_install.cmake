# Install script for directory: C:/Users/Desert Combat/source/repos/DungeonEscape/libs/k9/examples/ImGui_Example/Renderer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/SDL2/cmake_install.cmake")
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/SDL2_image/cmake_install.cmake")
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/SDL2_ttf/cmake_install.cmake")
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/Glad/cmake_install.cmake")
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/glm/cmake_install.cmake")
  include("C:/Users/Desert Combat/source/repos/DungeonEscape/sandbox/RenderTest/dirs/Renderer/libs/imgui/cmake_install.cmake")

endif()

