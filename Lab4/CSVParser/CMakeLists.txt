cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME CSVParser)
project(${PROJECT_NAME})
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
        PUBLIC
        include/CSVParser.h
        PRIVATE
        src/CSVParser.cpp)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)