cmake_minimum_required(VERSION 3.23)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
add_executable(Lab2 main.cpp ParserInputFile.cpp ParserInputFile.h UiManager.cpp UiManager.h LifeManager.cpp LifeManager.h FieldManager.cpp FieldManager.h GameManager.cpp GameManager.h GameParams.h)