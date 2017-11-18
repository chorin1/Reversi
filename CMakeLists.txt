cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Board.cpp
        Board.h
        ConsoleView.cpp
        ConsoleView.h
        Controller.cpp
        Controller.h
        GameModel.cpp
        GameModel.h
		HumanPlayer.cpp
        HumanPlayer.h
        main.cpp
        Player.h
        View.h
		AIPlayer.cpp
		AIPlayer.h)

add_definitions(-std=c++98)
add_executable(Reversi ${SOURCE_FILES} main.cpp)
