cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Board.cpp
        Board.h
        main.cpp
        ConsoleView.cpp GameModel.cpp)

add_executable(Reversi ${SOURCE_FILES} ConsoleView.cpp GameModel.cpp)