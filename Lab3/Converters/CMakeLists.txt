cmake_minimum_required(VERSION 3.21)
project(Converters)
set(SOURCE_LIB)
add_library(Converters STATIC)

include_directories(../WAVFileManager)
target_link_libraries(${PROJECT_NAME} WAVFileManager)
target_sources(Converters
        PUBLIC
        IConverter/IConverter.h
        MuteConverter/include/MuteConverter.h
        MixConverter/include/MixConverter.h
        FlexConverter/include/FlexConverter.h
        Tags.h
        FactoryItems.h
        PRIVATE
        FactoryItems.cpp
        FlexConverter/src/FlexConverter.cpp
        MixConverter/src/MixConverter.cpp
        MuteConverter/src/MuteConverter.cpp)
target_include_directories(Converters
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/MuteConverter/src
        ${CMAKE_CURRENT_SOURCE_DIR}/MixConverter/src
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexConverter/src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MuteConverter/include
        ${CMAKE_CURRENT_SOURCE_DIR}/MixConverter/include
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexConverter/include
        ${CMAKE_CURRENT_SOURCE_DIR}/IConverter
)