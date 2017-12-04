cmake_minimum_required(VERSION 3.8)
project(Reversi)
set(CMAKE_CXX_STANDARD 98)

file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_library(ReversiGame STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(Reversi ${SOURCE_FILES} src/Server.cpp src/Server.h)

add_subdirectory(tests)

target_link_libraries(Reversi ReversiGame)
