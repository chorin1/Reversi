cmake_minimum_required(VERSION 3.8)
project(ex3new)
set(CMAKE_CXX_STANDARD 98)

file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_library(ReversiGame STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(Reversi ${SOURCE_FILES} )

add_subdirectory(tests)

add_subdirectory(server)

target_link_libraries(Reversi ReversiGame)
