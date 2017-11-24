//
// Created by chorin on 24/11/2017.
//
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

GTEST_API_ int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::cin.get();
    return 0;
}