
//
// Created by nitaihalle on 11/26/17.
//
#include <gtest/gtest.h>
#include "GameModel.h"
#include "ConsoleView.h"
class GameModelTest : public testing::Test{
    public:
        GameModelTest(): testView(testModel){};
        virtual void SetUp() {
            std::cout << "Setting up..." << std::endl;
            //set up scenario
            testModel1.setCellAt(GameModel::Pos(4,4),Board::CELL_PLAYER1);
            testModel1.setCellAt(GameModel::Pos(5,5),Board::CELL_PLAYER1);
            testModel1.setCellAt(GameModel::Pos(5,4),Board::CELL_PLAYER2);
            testModel1.setCellAt(GameModel::Pos(4,5),Board::CELL_PLAYER2);

            testModel1.setCellAt(GameModel::Pos(8,8),Board::CELL_PLAYER2);
            testModel1.setCellAt(GameModel::Pos(8,7),Board::CELL_PLAYER1);

            testModel1.setCellAt(GameModel::Pos(3,3),Board::CELL_PLAYER1);
            testModel1.setCellAt(GameModel::Pos(3,4),Board::CELL_PLAYER1);
            testModel1.setCellAt(GameModel::Pos(3,5),Board::CELL_PLAYER1);
            testModel1.setCellAt(GameModel::Pos(3,6),Board::CELL_PLAYER1);

            testModel1.setCellAt(GameModel::Pos(3,7),Board::CELL_PLAYER2);
            testModel1.setCellAt(GameModel::Pos(3,8),Board::CELL_PLAYER1);

            testModel1.updatePossibleMoves(GameModel::PLAYER1);
            testModel1.updatePossibleMoves(GameModel::PLAYER2);
        }
        virtual void TearDown() {
            std::cout << "Tearing down..." << std::endl;
        }

    protected:

        GameModel testModel;
        GameModel testModel1;
        GameModel testModel3;
        ConsoleView testView;
};
TEST_F(GameModelTest, basicTest){
    EXPECT_TRUE(testModel.isAbleToMove(GameModel::PLAYER1));

}