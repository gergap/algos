project(test C)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(unittest)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(../testlib)

set(TEST_LIBS sort)
add_unit_test(quicksort quicksort.c)

