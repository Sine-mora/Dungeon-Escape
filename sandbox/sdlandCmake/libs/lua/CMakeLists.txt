#add_compile_definitions(LUA_VERSION_NUM="5.3.6")

set(LUA_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include" PARENT_SCOPE)

SOURCE_FILES(lua_source_list src)
add_library(lua_lib ${lua_source_list})