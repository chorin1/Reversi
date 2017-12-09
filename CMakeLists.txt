cmake_minimum_required(VERSION 3.8)
project(Reversi)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../exe")

file(GLOB HEADER_FILES src/Client/include/*.h)
file(GLOB SOURCE_FILES src/Client/src/*.cpp)

add_executable(ReversiGame ${SOURCE_FILES} ${HEADER_FILES})
# add as library for google test
add_library(ReversiLib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(src/Client/tests)
add_subdirectory(src/Server)