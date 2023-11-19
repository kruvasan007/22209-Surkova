cmake_minimum_required(VERSION 3.21)
project(Factory)
set(SOURCE_LIB )
add_library(Factory STATIC)
target_sources(Factory
        PUBLIC
        include/FactoryAliasNames.h
        include/FactoryCreator.h
        include/IFactory.h
        include/Tag.h
        PRIVATE
        src/Factory.cpp
        src/Factory.h
        src/FactoryCreator.cpp)

target_include_directories(Factory
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )