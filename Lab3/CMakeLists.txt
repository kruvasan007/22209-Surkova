cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME Lab3)

set(CMAKE_CXX_STANDARD 17)
include_directories(Utils)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Utils)
add_subdirectory(WAVFileManager)
add_subdirectory(Converters)
add_subdirectory(Factory)

target_link_libraries(${PROJECT_NAME} Utils)
target_link_libraries(${PROJECT_NAME} WAVFileManager)
target_link_libraries(${PROJECT_NAME} Converters)
target_link_libraries(${PROJECT_NAME} Factory)