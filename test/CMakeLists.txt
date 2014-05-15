option(ENABLE_COLOR "Enable terminal color support" ON)
option(ENABLE_HEXDUMP "Enable hexdump support" ON)
option(ENABLE_BENCHMARK "Enable benchmark support" ON)

# platform check
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(ENABLE_COLOR OFF CACHE BOOL "Enable terminal color support" FORCE)
endif()

# check if we have getopt.h
include(CheckIncludeFile)
CHECK_INCLUDE_FILE("getopt.h" HAVE_GETOPT)
if (WIN32)
    if(exists ${CMAKE_SOURCE_DIR}/pthread-win32/getopt.c)
        # enable getopt support on Windows
        set(HAVE_GETOPT 1)
    endif()
endif()

# create config.h
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/test_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/test_config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG)

add_subdirectory(testlib)
add_subdirectory(sort)

