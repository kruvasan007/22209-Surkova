cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

enable_testing()
add_subdirectory(googletest)
add_executable(Lab1 test.cpp BitArray.cpp BitArray.h)
target_link_libraries(Lab1 gtest_main gmock_main)
