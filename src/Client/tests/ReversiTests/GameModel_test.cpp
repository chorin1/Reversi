/**
 * Unit testing for the GameModel - Reversi game
 */
#include <gtest/gtest.h>
#include "../../include/GameModel.h"
#include "../../include/ConsoleView.h"
#include <algorithm>
class GameModelTest : public testing::Test{
	public:
		GameModelTest(): testView(testModel2){};
		virtual void SetUp() {
			std::cout << "Setting up..." << std::endl;
			//set up scenario 1
			testModel1.setCellAt(GameModel::Pos(4,4),Board::CELL_PLAYER1);
			testModel1.setCellAt(GameModel::Pos(5,5),Board::CELL_PLAYER1);
			testModel1.setCellAt(GameModel::Pos(5,4),Board::CELL_PLAYER2);
			testModel1.setCellAt(GameModel::Pos(4,5),Board::CELL_PLAYER2);
			//update moves.
			testModel1.updatePossibleMoves(GameModel::PLAYER1);
			testModel1.updatePossibleMoves(GameModel::PLAYER2);

			//set up scenario 2
			testModel2.setCellAt(GameModel::Pos(1,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(2,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(3,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(4,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(5,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(6,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(7,1),Board::CELL_PLAYER1);
			testModel2.setCellAt(GameModel::Pos(8,1),Board::CELL_PLAYER1);

			testModel2.setCellAt(GameModel::Pos(1,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(2,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(3,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(4,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(5,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(6,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(7,2),Board::CELL_PLAYER2);
			testModel2.setCellAt(GameModel::Pos(8,2),Board::CELL_PLAYER2);

			testModel2.setCellAt(GameModel::Pos(4,4),Board::CELL_EMPTY);
			testModel2.setCellAt(GameModel::Pos(5,5),Board::CELL_EMPTY);
			testModel2.setCellAt(GameModel::Pos(5,4),Board::CELL_EMPTY);
			testModel2.setCellAt(GameModel::Pos(4,5),Board::CELL_EMPTY);

			testModel2.updatePossibleMoves(GameModel::PLAYER1);
			testModel2.updatePossibleMoves(GameModel::PLAYER2);

			//set up scenario 3
			testModel3.setCellAt(GameModel::Pos(1,1),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(2,2),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(3,3),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(4,4),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(5,5),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(6,6),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(7,7),Board::CELL_PLAYER1);
			testModel3.setCellAt(GameModel::Pos(8,8),Board::CELL_PLAYER1);

			testModel3.setCellAt(GameModel::Pos(1,2),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(2,3),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(3,4),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(4,5),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(5,6),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(6,7),Board::CELL_PLAYER2);
			testModel3.setCellAt(GameModel::Pos(7,8),Board::CELL_PLAYER2);


			testModel3.setCellAt(GameModel::Pos(5,4),Board::CELL_EMPTY);

			testModel3.updatePossibleMoves(GameModel::PLAYER1);
			testModel3.updatePossibleMoves(GameModel::PLAYER2);
		}
		virtual void TearDown() {
			std::cout << "Tearing down..." << std::endl;
		}

	protected:

		GameModel testModel;
		GameModel testModel1;
		GameModel testModel2;
		GameModel testModel3;
		ConsoleView testView;
};
TEST_F(GameModelTest, basicTest){
	//test if the players can move.
	EXPECT_TRUE(testModel1.isAbleToMove(GameModel::PLAYER1));
	EXPECT_TRUE(testModel1.isAbleToMove(GameModel::PLAYER2));
	//check if the size of the vector from getPossibleMoves it correct.
	EXPECT_EQ(4, testModel1.getPossibleMoves(GameModel::PLAYER1)->size());
	//put players cells in the testModel and check if this happen.
	EXPECT_TRUE(testModel1.place(GameModel::PLAYER2, GameModel::Pos(5, 6)));
	EXPECT_TRUE(testModel1.place(GameModel::PLAYER1, GameModel::Pos(4, 6)));


	testModel1.updatePossibleMoves(GameModel::PLAYER1);
	testModel1.updatePossibleMoves(GameModel::PLAYER2);

	//check if the size of the vector from getPossibleMoves it correct.
	EXPECT_EQ(5, testModel1.getPossibleMoves(GameModel::PLAYER1)->size());
	//test the function getBoardSize.
	EXPECT_EQ(testModel1.getBoardSize(), 8);
	//test the function getCellAt.
	EXPECT_EQ(testModel.getCellAt(GameModel::Pos(5,9)),Board::CELL_ERROR);
	EXPECT_EQ(testModel.getCellAt(GameModel::Pos(1,1)),Board::CELL_EMPTY);
	//check the function isPossibleMove.
	EXPECT_TRUE(testModel1.isPossibleMove(GameModel::PLAYER1,GameModel::Pos(6,6)));
	//check if the score is accurate.
	EXPECT_EQ(testModel1.calcScoreOf(GameModel::PLAYER1), 3);
}
TEST_F(GameModelTest, edgeTest){
	GameModel overSize(1000);
	GameModel underSize(2);
	GameModel size6(6);
	GameModel copy(size6);
	//check if the size of the board is In the right range,or if it in the right size.
	EXPECT_EQ(overSize.getBoardSize(),8);
	EXPECT_EQ(underSize.getBoardSize(),8);
	EXPECT_EQ(copy.getBoardSize(),6);

	//test scenario 2.
	//test if the players can move.
	EXPECT_TRUE(testModel2.isAbleToMove(GameModel::PLAYER1));
	EXPECT_FALSE(testModel2.isAbleToMove(GameModel::PLAYER2));
	//check if the size of the vector from getPossibleMoves it correct.
	EXPECT_EQ(8, testModel2.getPossibleMoves(GameModel::PLAYER1)->size());

	//test if all the cells in correct position.

	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(1,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(2,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(3,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(4,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(5,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(6,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(7,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(8,1)),Board::CELL_PLAYER1);

	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(1,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(2,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(3,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(4,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(5,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(6,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(7,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(8,2)),Board::CELL_PLAYER2);

	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(1,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(2,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(3,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(4,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(5,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(6,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(7,3)),Board::CELL_EMPTY);
	EXPECT_EQ(testModel2.getCellAt(GameModel::Pos(8,3)),Board::CELL_EMPTY);

	const std::vector<GameModel::Pos> *vec = testModel2.getPossibleMoves(GameModel::PLAYER1);
	//test if the size is correct.
	EXPECT_EQ(vec->size(), 8);
	//check if all the pos is correct
	int i=1;
	for (std::vector<GameModel::Pos>::const_iterator it = vec->begin(); it != vec->end(); ++it) {
		EXPECT_TRUE((GameModel::Pos)*it == GameModel::Pos(i,3));
		i++;
	}
	//test the function calcScoreOf.
	EXPECT_EQ(testModel2.calcScoreOf(GameModel::PLAYER1),8);
	EXPECT_EQ(testModel2.calcScoreOf(GameModel::PLAYER2),8);

	//test scenario 3.

	//test if the players can move.
	EXPECT_TRUE(testModel3.isAbleToMove(GameModel::PLAYER1));
	EXPECT_TRUE(testModel3.isAbleToMove(GameModel::PLAYER2));


	//test if all the cells in correct position.

	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(1,1)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(2,2)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(3,3)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(4,4)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(5,5)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(6,6)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(7,7)),Board::CELL_PLAYER1);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(8,8)),Board::CELL_PLAYER1);

	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(1,2)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(2,3)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(3,4)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(4,5)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(5,6)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(6,7)),Board::CELL_PLAYER2);
	EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(7,8)),Board::CELL_PLAYER2);

	for(int i = 2; i < 9; i++){
		for(int j = 1; j < i; j++){
			EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(i,j)),Board::CELL_EMPTY);
		}
	}

	for(int i = 1; i < 8; i++){
		for(int j = i + 2; j < 9; j++){
			EXPECT_EQ(testModel3.getCellAt(GameModel::Pos(i,j)),Board::CELL_EMPTY);
		}
	}

	//check if the size of the vector from getPossibleMoves it correct.
	EXPECT_EQ(6, testModel3.getPossibleMoves(GameModel::PLAYER1)->size());

	const std::vector<GameModel::Pos> *vec2 = testModel3.getPossibleMoves(GameModel::PLAYER1);
	//check if all the pos of possible moves is correct
	i=1;
	for (std::vector<GameModel::Pos>::const_iterator it = vec2->begin(); it != vec2->end(); ++it) {
		EXPECT_TRUE((GameModel::Pos)*it == GameModel::Pos(i,i+2));
		i++;
	}
}
