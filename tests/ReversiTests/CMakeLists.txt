include_directories(${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${gmock_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../exe")
add_executable(ReversiTests main.cpp AIPlayer_test.cpp Board_test.cpp GameModel_test.cpp HumanPlayer_test.cpp)

target_link_libraries(ReversiTests gtest gtest_main)
target_link_libraries(ReversiTests ReversiLib)
