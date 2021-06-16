# Set the SOL_PATH variable to be used in the parent CMakeLists.txt scope
set(EXTERN_SOL_PATH ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

include_directories(${LUA_INCLUDE_DIRS})

