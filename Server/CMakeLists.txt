cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 98)
project(Reversi)

set(serSOURCE_FILES main.cpp Server.cpp Server.h)
add_executable(ReversiServer ${serSOURCE_FILES})