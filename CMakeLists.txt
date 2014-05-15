project(algos C)
cmake_minimum_required(VERSION 2.8)

# enable warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(WARNINGS "-Wall -Wextra -Wformat=2 -Woverflow -Wundef -Wstrict-aliasing -Wshadow")
    set(WARNINGS "${WARNINGS} -Wpointer-arith -Wcast-align -Wwrite-strings -Wlogical-op")
    set(WARNINGS "${WARNINGS} -Waggregate-return -Wmissing-noreturn -Wbuiltin-macro-redefined")
    set(WARNINGS "${WARNINGS} -Wpointer-to-int-cast -Wpragmas -Wsuggest-attribute=const")
    set(WARNINGS "${WARNINGS} -Wsync-nand -Wattributes")
    # enable this to enforce strict C prototypes: e.g. int foo(void);
    set(WARNINGS "${WARNINGS} -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition")
    # warn if a global function is defined without a previous declaration.
    set(WARNINGS "${WARNINGS} -Wmissing-declarations")
    # enable all warnings
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 ${WARNINGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99 ${WARNINGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker -Map=output.map")
endif()

add_subdirectory(sort)

#######################
# Unit Test Framework
SET(BUILDNAME "${PRODUCTFULLNAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}-${GIT_BRANCH}")
SET(UPDATE_TYPE "git")
# enable unittests
enable_testing()
# enable CDash
include(CTest)
if (BUILD_TESTING)
    add_subdirectory(test)
endif()
