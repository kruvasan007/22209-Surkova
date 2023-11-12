cmake_minimum_required(VERSION 3.21)
project(WAVFileManager)
add_library(WAVFileManager STATIC)
target_sources(WAVFileManager
        PUBLIC
        include/WAVHeader.h
        include/WAVHeaderParser.h
        include/WAVStreamWriter.h
        include/WAVStreamReader.h
        PRIVATE
        src/WAVStreamWriter.cpp
        src/WAVStreamReader.cpp
        src/WAVHeaderParser.cpp)
target_include_directories(WAVFileManager
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )