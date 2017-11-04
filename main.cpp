/*
 * main.cpp
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 *  ID: 021906185
 */
#include "Board.h"

int main() {
	Board* sampleBoard = new Board(8);
	sampleBoard->draw();
	delete sampleBoard;
	return 0;
}



