cmake_minimum_required(VERSION 3.8)
project(Reversi)
set(CMAKE_CXX_STANDARD 98)

file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(ReversiGame ${SOURCE_FILES} ${HEADER_FILES})
# add as library for google test
add_library(ReversiLib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(tests)
add_subdirectory(Server)
