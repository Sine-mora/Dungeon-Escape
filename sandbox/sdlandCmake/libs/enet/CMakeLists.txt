cmake_minimum_required(VERSION 3.7.2)

project(enet)

# The "configure" step.
include(CheckFunctionExists)
include(CheckStructHasMember)
include(CheckTypeSize)
check_function_exists("fcntl" HAS_FCNTL)
check_function_exists("poll" HAS_POLL)
check_function_exists("getaddrinfo" HAS_GETADDRINFO)
check_function_exists("getnameinfo" HAS_GETNAMEINFO)
check_function_exists("gethostbyname_r" HAS_GETHOSTBYNAME_R)
check_function_exists("gethostbyaddr_r" HAS_GETHOSTBYADDR_R)
check_function_exists("inet_pton" HAS_INET_PTON)
check_function_exists("inet_ntop" HAS_INET_NTOP)
check_struct_has_member("struct msghdr" "msg_flags" "sys/types.h;sys/socket.h" HAS_MSGHDR_FLAGS)
set(CMAKE_EXTRA_INCLUDE_FILES "sys/types.h" "sys/socket.h")
check_type_size("socklen_t" HAS_SOCKLEN_T BUILTIN_TYPES_ONLY)
unset(CMAKE_EXTRA_INCLUDE_FILES)
if(MSVC)
	add_definitions(-W3)
else()
	add_definitions(-Wno-error)
endif()

if(HAS_FCNTL)
    add_definitions(-DHAS_FCNTL=1)
endif()
if(HAS_POLL)
    add_definitions(-DHAS_POLL=1)
endif()
if(HAS_GETNAMEINFO)
    add_definitions(-DHAS_GETNAMEINFO=1)
endif()
if(HAS_GETADDRINFO)
    add_definitions(-DHAS_GETADDRINFO=1)
endif()
if(HAS_GETHOSTBYNAME_R)
    add_definitions(-DHAS_GETHOSTBYNAME_R=1)
endif()
if(HAS_GETHOSTBYADDR_R)
    add_definitions(-DHAS_GETHOSTBYADDR_R=1)
endif()
if(HAS_INET_PTON)
    add_definitions(-DHAS_INET_PTON=1)
endif()
if(HAS_INET_NTOP)
    add_definitions(-DHAS_INET_NTOP=1)
endif()
if(HAS_MSGHDR_FLAGS)
    add_definitions(-DHAS_MSGHDR_FLAGS=1)
endif()
if(HAS_SOCKLEN_T)
    add_definitions(-DHAS_SOCKLEN_T=1)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

# Support both 32 and 64 bit builds
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	  set(ENET_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x64")
	else ()
	  set(ENET_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x86")

	endif ()

	# Set the static libraries to be added
	set(ENET_LIB "${ENET_LIBS_PATH}/enet.lib")
	string(STRIP "${ENET_LIB}" ENET_LIB)

    set(ENET_X64_WS2_WINM "${ENET_LIB};ws2_32.lib;winmm.lib" PARENT_SCOPE)


set(INCLUDE_FILES_PREFIX include/enet)
set(ENET_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/enet" PARENT_SCOPE)
set(INCLUDE_FILES
    ${INCLUDE_FILES_PREFIX}/callbacks.h
    ${INCLUDE_FILES_PREFIX}/enet.h
    ${INCLUDE_FILES_PREFIX}/list.h
    ${INCLUDE_FILES_PREFIX}/protocol.h
    ${INCLUDE_FILES_PREFIX}/time.h
    ${INCLUDE_FILES_PREFIX}/types.h
    ${INCLUDE_FILES_PREFIX}/unix.h
    ${INCLUDE_FILES_PREFIX}/utility.h
    ${INCLUDE_FILES_PREFIX}/win32.h
)

set(SOURCE_FILES
    callbacks.c
    compress.c
    host.c
    list.c
    packet.c
    peer.c
    protocol.c
    unix.c
    win32.c)

source_group(include FILES ${INCLUDE_FILES})
source_group(source FILES ${SOURCE_FILES})

add_library(enet STATIC
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

if (MINGW)
    target_link_libraries(enet winmm ws2_32)
endif()
