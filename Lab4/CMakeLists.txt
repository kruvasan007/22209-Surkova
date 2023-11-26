cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME Lab4)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(CSVParser)
target_link_libraries(${PROJECT_NAME} CSVParser)