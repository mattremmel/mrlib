# CMake
cmake_minimum_required(VERSION 3.2)


# Project
project(mrlib)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.$VERSION_PATCH}")

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Headers / Source

### Project ###
set(HEADER_CORE mrlib/core)
set(HEADER_UTIL mrlib/util)
set(HEADER_CONT mrlib/container)
set(HEADER_SYS  mrlib/system)
set(HEADER_NET  mrlib/network)
set(HEADER_ALL  ${HEADER_CORE} ${HEADER_UTIL} ${HEADER_CONT} ${HEADER_SYS} ${HEADER_NET})


### Test Source ###
set(TEST_SOURCE test/containers/String_Test.cpp test/containers/Array_Test.cpp test/containers/Dictionary_Test.cpp test/util/Random_Test.cpp test/util/Stopwatch_Test.cpp test/util/Logging_Test.cpp test/util/Timer_Test.cpp)

### Testing Framework ###
set(TEST_FRAMEWORK_MAIN test/googletest-1.7.0/gtest_main.cc)
set(TEST_FRAMEWORK_HEADERS test/googletest-1.7.0)
set(TEST_FRAMEWORK_SOURCE test/googletest-1.7.0/gtest-all.cc)
set(TEST_FRAMEWORK_ALL ${TEST_FRAMEWORK_MAIN} ${TEST_FRAMEWORK_HEADERS} ${TEST_FRAMEWORK_SOURCE})


# Include Headers
include_directories(${HEADER_ALL} ${TEST_FRAMEWORK_HEADERS})


# Executables

### Testing Executable ###
add_executable(mrlib-test ${TEST_FRAMEWORK_ALL} ${TEST_SOURCE})