cmake_minimum_required(VERSION 3.23)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

enable_testing()
add_subdirectory(googletest)
add_executable(Lab2 test.cpp UiManager.cpp UiManager.h LifeManager.cpp LifeManager.h FieldManager.cpp FieldManager.h GameManager.cpp GameManager.h FileData.h)
target_link_libraries(Lab2 gtest_main gmock_main)