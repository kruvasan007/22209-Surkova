cmake_minimum_required(VERSION 3.23)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
add_subdirectory(googletest)
add_executable(Lab1 test.cpp BitArray.cpp BitArray.h ../Lab2/main.cpp ../Lab2/FieldManager.cpp ../Lab2/FieldManager.h ../Lab2/LifeManager.cpp ../Lab2/LifeManager.h ../Lab2/Cell.h ../Lab2/UiManager.cpp ../Lab2/UiManager.h)
target_link_libraries(Lab1 gtest_main gmock_main)