/**
 * Unit testing for a board used in reversi game
 */


#include "gtest/gtest.h"
#include "../../include/Board.h"
class BoardTest : public testing::Test{
public:
	BoardTest():b1(8),b2(10),b3(b2){}
protected:
	Board b1,b2,b3;
};

//test size of Board.
TEST_F(BoardTest ,Board_test1){
	EXPECT_EQ(b1.getBoardSize(),8);
	EXPECT_EQ(b2.getBoardSize(),10);
	EXPECT_EQ(b3.getBoardSize(),10);
};
//check if the intilaize is correct.
TEST_F(BoardTest ,Board_test2){
	int centerB1 = b1.getBoardSize()/2;
	int centerB2 = b2.getBoardSize()/2;
	EXPECT_EQ(b1.getCellAt(centerB1 ,centerB1),Board::CELL_PLAYER2);
	EXPECT_EQ(b1.getCellAt(centerB1 - 1 ,centerB1 - 1),Board::CELL_PLAYER2);
	EXPECT_EQ(b1.getCellAt(centerB1 - 1,centerB1),Board::CELL_PLAYER1);
	EXPECT_EQ(b1.getCellAt(centerB1 ,centerB1 - 1),Board::CELL_PLAYER1);
	EXPECT_EQ(b1.getCellAt(b1.getBoardSize() - 1,b1.getBoardSize() - 1),Board::CELL_EMPTY);
	EXPECT_EQ(b2.getCellAt(centerB2 ,centerB2),Board::CELL_PLAYER2);
	EXPECT_EQ(b2.getCellAt(centerB2 - 1 ,centerB2 - 1),Board::CELL_PLAYER2);
	EXPECT_EQ(b2.getCellAt(centerB2 - 1,centerB2),Board::CELL_PLAYER1);
	EXPECT_EQ(b2.getCellAt(centerB2 ,centerB2 - 1),Board::CELL_PLAYER1);
	EXPECT_EQ(b2.getCellAt(b2.getBoardSize() - 1,b2.getBoardSize() - 1),Board::CELL_EMPTY);



};
