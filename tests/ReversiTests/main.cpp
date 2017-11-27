/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #4
 *	Group: 04
 *  Date: 27/11/17
 *
 *  main file used for testing Reversi classes using google test
 */
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

GTEST_API_ int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::cin.get();
    return 0;
}