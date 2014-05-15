# Provides a macro for creating unittest executables using
# the C Unit Test Framework.
# Copyright (C) 2014 Gerhard Gappmeier <gappy1502@gmx.net>
#
# Requirements:
# * you need to enable testing using 'enable_testing()' in your top-level
#   CMake file.
# * if you want to support CDash you need to add
#   'include(CTest)' in your top-level cmake file.
#
# Usage:
#  ADD_UNIT_TEST(<TestName> <Source>)
# Example:
#  ADD_UNIT_TEST(String teststring.c)
#
# This creates an executable named test_<TestName> and add a CMake test
# with the same name. Add also adds the test to the INSTALL target, so that
# 'make install' will install them into ${CMAKE_INSTALL_PREFIX}/bin. When
# running the tests using 'make test' it will also use this directory as the
# WORKING_DIRECTORY.
#
# There are two variables you can use to customize the build of unit test
# executables.
#
# * additional sources to compile with each test
#   set(TEST_ADDITIONAL <sources>)
# * libraries to link with each test
#   set(TEST_LIBS <libraries>)
#
# You can change the default working directory of the tests by overriding the
# variable TEST_WORKING_DIRECORY.
# Note: The default dir may cause problems when using relative INSTALL_PREFIX
# like ../dist. Therefore it is recommended to use absolute paths like
# /usr/local.

# default value
set(TEST_WORKING_DIRECORY ${CMAKE_SOURCE_DIR}/bin)
set(TARGET "root@192.168.10.2")

# macro for creating unit test executables
macro(ADD_UNIT_TEST testname testsrc)
    set(test_${testname}_SRCS ${testsrc})

    add_executable(test_${testname} ${test_${testname}_SRCS} ${TEST_ADDITIONAL})
    target_link_libraries(test_${testname} testlib ${TEST_LIBS})

    install(TARGETS test_${testname} RUNTIME DESTINATION bin)

    if(NOT CROSS_COMPILING)
        add_test(
            NAME test_${testname}
            COMMAND test_${testname} -s
            WORKING_DIRECTORY ${TEST_WORKING_DIRECORY})
    else()
        add_test(
            NAME test_${testname}
            COMMAND ssh ${TARGET} /root/bin/test_${testname} -s
            WORKING_DIRECTORY ${TEST_WORKING_DIRECORY})
    endif()
endmacro(ADD_UNIT_TEST)

