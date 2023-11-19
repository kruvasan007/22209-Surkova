cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME Utils)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
add_library(Utils STATIC)

include_directories(../WAVFileManager)
include_directories(../Factory)
include_directories(../Converters)
target_link_libraries(${PROJECT_NAME} WAVFileManager)
target_link_libraries(${PROJECT_NAME} Factory)
target_link_libraries(${PROJECT_NAME} Converters)

target_sources(Utils
        PUBLIC
        include/Configurator.h
        include/Errors.h
        PRIVATE
        src/Configurator.cpp
        src/Error.cpp)

target_include_directories(Utils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

