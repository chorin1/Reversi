cmake_minimum_required(VERSION 3.8)
project(Reversi)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../exe")
add_executable(ServerReversi main.cpp Server.cpp Server.h)