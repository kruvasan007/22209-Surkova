cmake_minimum_required(VERSION 3.23)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
add_subdirectory(googletest)
add_executable(Lab1 test.cpp BitArray.cpp BitArray.h)
target_link_libraries(Lab1 gtest_main gmock_main)