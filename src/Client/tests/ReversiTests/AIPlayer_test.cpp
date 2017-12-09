/**
 * Unit testing for the AIPlayer (minimax algo)
 */
#include "gtest/gtest.h"
#include "../../include/AIPlayer.h"
#include "../../include/GameModel.h"
#include "../../include/ConsoleView.h"
#include <iostream>

class AIPlayerTest: public testing::Test {
public:
	AIPlayerTest(): ai1(), testView(testModel){}

	virtual void SetUp() {
		std::cout << "Setting up..." << std::endl;
		noMovesp1m.m_possibleMovesPlayer1.clear();
		noMovesp2m.m_possibleMovesPlayer2.clear();

		//set up full board
		for (int i=1; i <= fullBoard.getBoardSize(); i++) {
			for (int j=1; j <= fullBoard.getBoardSize(); j++) {
				fullBoard.setCellAt(GameModel::Pos(i,j),Board::CELL_PLAYER1);
			}
		}
		fullBoard.updatePossibleMoves(GameModel::PLAYER1);
		fullBoard.updatePossibleMoves(GameModel::PLAYER2);

		//set up scenario 2
		testModel2.setCellAt(GameModel::Pos(4,4),Board::CELL_EMPTY);
		testModel2.setCellAt(GameModel::Pos(4,5),Board::CELL_EMPTY);
		testModel2.setCellAt(GameModel::Pos(5,4),Board::CELL_EMPTY);
		testModel2.setCellAt(GameModel::Pos(5,5),Board::CELL_EMPTY);

		testModel2.setCellAt(GameModel::Pos(1,5),Board::CELL_PLAYER2);
		testModel2.setCellAt(GameModel::Pos(2,5),Board::CELL_PLAYER1);

		testModel2.setCellAt(GameModel::Pos(3,3),Board::CELL_PLAYER1);
		testModel2.setCellAt(GameModel::Pos(3,4),Board::CELL_PLAYER1);
		testModel2.setCellAt(GameModel::Pos(3,5),Board::CELL_PLAYER1);
		testModel2.setCellAt(GameModel::Pos(3,6),Board::CELL_PLAYER1);

		testModel2.setCellAt(GameModel::Pos(3,7),Board::CELL_PLAYER2);
		testModel2.setCellAt(GameModel::Pos(3,8),Board::CELL_PLAYER1);

		testModel2.updatePossibleMoves(GameModel::PLAYER1);
		testModel2.updatePossibleMoves(GameModel::PLAYER2);

		//set up scn3
		testModel3.setCellAt(GameModel::Pos(3,4),Board::CELL_PLAYER1);
		testModel3.setCellAt(GameModel::Pos(3,5),Board::CELL_PLAYER1);

		testModel3.setCellAt(GameModel::Pos(3,3),Board::CELL_PLAYER2);
		testModel3.setCellAt(GameModel::Pos(4,6),Board::CELL_PLAYER2);

		testModel3.updatePossibleMoves(GameModel::PLAYER1);
		testModel3.updatePossibleMoves(GameModel::PLAYER2);

	}
	virtual void TearDown() {
		std::cout << "Tearing down..." << std::endl;
	}
protected:
	AIPlayer ai1;
	GameModel testModel;
	GameModel testModel2;
	GameModel testModel3;
	GameModel noMovesp1m;
	GameModel noMovesp2m;
	GameModel fullBoard;
	ConsoleView testView;
};

TEST_F (AIPlayerTest, basicTest) {
	//testView.drawBoard();
	EXPECT_NE(ai1.makeMove(&testModel), GameModel::Pos(0,0));
	//AI has 2 moves resulting in same score, chooses the first one
	EXPECT_EQ(ai1.makeMove(&testModel), GameModel::Pos(3,5));

	//example from Ex3 pdf
	testModel.place(GameModel::PLAYER1, GameModel::Pos(3,4));
	//testView.drawBoard();
	EXPECT_EQ(ai1.makeMove(&testModel), GameModel::Pos(3,3));

	//scn 2 - AI doesnt try to get easy points..
	testView.setView(testModel2);
	//testView.drawBoard();
	EXPECT_NE(ai1.makeMove(&testModel2), GameModel::Pos(3,2));
	EXPECT_EQ(ai1.makeMove(&testModel2), GameModel::Pos(4,5));

	//scn 3 - AI chooses minimax properly (2 moves with same score to computer but diff score to opponent)
	testView.setView(testModel3);
	//testView.drawBoard();
	EXPECT_NE(ai1.makeMove(&testModel3), GameModel::Pos(3,6));
}

TEST_F (AIPlayerTest, edgeTests) {
	// pass a null pointer to board
	EXPECT_EQ(ai1.makeMove(NULL), GameModel::Pos(0,0));
	//AI has no possible moves
	EXPECT_EQ(ai1.makeMove(&noMovesp2m), GameModel::Pos(0,0));
	// Board is full
	testView.setView(fullBoard);
	//testView.drawBoard();
	EXPECT_EQ(ai1.makeMove(&fullBoard), GameModel::Pos(0,0));
	//opponent has no possible moves, AI should choose a move
	EXPECT_NE(ai1.makeMove(&noMovesp1m), GameModel::Pos(0,0));
}
