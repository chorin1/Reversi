cmake_minimum_required(VERSION 3.8)
project(Reversi)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../exe")

add_executable(Server ${SERVER_ICNLUDE} ${SERVER_SOURCE})