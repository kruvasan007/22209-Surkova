cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME Lab3)

set(CMAKE_CXX_STANDARD 17)

include_directories(WAVFileManager)
include_directories(Factory)
include_directories(Converters)
include_directories(Configurator)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp Configurator/Configurator.cpp Configurator/Configurator.h Errors.h Error.cpp)

add_subdirectory(WAVFileManager)
add_subdirectory(Factory)
add_subdirectory(Converters)
target_link_libraries(${PROJECT_NAME} WAVFileManager)
target_link_libraries(${PROJECT_NAME} Factory)
target_link_libraries(${PROJECT_NAME} Converters)