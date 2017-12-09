/**
 * Unit testing for the Human Player - Reversi game
 */


#include "gtest/gtest.h"
#include "../../include/HumanPlayer.h"
#include "../../include/GameModel.h"
#include <iostream>
#include <ctime>

using namespace std;

TEST (HumanPlayerTest, sanityCheck) {
	HumanPlayer p1;
	istringstream s1("1,1");
	cin.rdbuf(s1.rdbuf());
	EXPECT_EQ(p1.makeMove(), GameModel::Pos(1, 1));
	istringstream s2("10,5");
	cin.rdbuf(s2.rdbuf());
	EXPECT_EQ(p1.makeMove(), GameModel::Pos(10, 5));
}

TEST (HumanPlayerTest, randomInput) {
	HumanPlayer p1;
	const int testSize = 10;
	srand((int)time(0));
	istringstream rndInput[testSize];

	//create random points inserted by player within board limits
	for (int i=0; i < testSize; i++) {
		int r1 = rand() % GameModel::MAX_BOARD_SIZE + 1;
		int r2 = rand() % GameModel::MAX_BOARD_SIZE + 1;
		string s1 = static_cast<ostringstream *>( &(ostringstream() << r1))->str();
		string s2 = static_cast<ostringstream *>( &(ostringstream() << r2))->str();
		rndInput[i].str(s1 + "," + s2);

		cin.rdbuf(rndInput[i].rdbuf());
		EXPECT_EQ(p1.makeMove(), GameModel::Pos(r1, r2));
	}
}