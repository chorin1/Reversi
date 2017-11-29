include_directories(${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${gmock_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include)
add_executable(ReversiTests main.cpp AIPlayer_test.cpp Board_test.cpp GameModel_test.cpp HumanPlayer_test.cpp)

target_link_libraries(ReversiTests gtest gtest_main)
target_link_libraries(ReversiTests ReversiGame)
