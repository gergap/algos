project(test C)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(test main.c)
target_link_libraries(test sort)

