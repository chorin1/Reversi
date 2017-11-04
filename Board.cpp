/*
 * Board.cpp
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 *  ID: 021906185
 */

#include "Board.h"
#include <iostream>
#include <assert.h>
using namespace std;


Board::Board(int boardSize = 8): m_boardSize(boardSize) {
	m_board = new Cell [m_boardSize * m_boardSize];
	initBoard();
}

void Board::initBoard() {
	assert(Board::m_boardSize > 3 || Board::m_boardSize < 20);
        int center = Board::m_boardSize / 2;
        for (int i = 0; i < Board::m_boardSize; i++) {
            for (int j = 0; j < Board::m_boardSize; j++) {
				if ((j == center - 1 && i == center - 1) || (j == center && i == center))
					Board::setCellValue(i, j, Board::CELL_O);
                else if ((j == center - 1 && i == center) || (j == center && i == center - 1))
					Board::setCellValue(i, j, Board::CELL_X);
                else
					Board::setCellValue(i, j, Board::CELL_EMPTY);
            }
        }
}

Board::~Board() {
	delete [] m_board;
}

void Board::drawFirstRow() const {
	cout << " |";
	for (int i=1; i<= m_boardSize; i++) {
		cout << " " << i << " |";
	}
	cout << endl;
}

void Board::drawCompleteLine() const {
	cout << "--";
	for (int i=1; i<= Board::m_boardSize; i++) {
		cout << "----";
	}
	cout << endl;

}

void Board::drawRow(int row) const {
	cout << row+1 << "|";
	for (int i=0; i < Board::m_boardSize; i++) {
		cout << " ";
		switch (Board::getCellAt(row, i)) {
		case Board::CELL_EMPTY:
			cout << " ";
			break;
		case Board::CELL_X:
			cout << "X";
			break;
		case Board::CELL_O:
			cout << "O";
			break;
		default:
			cout << "E"; //error
			break;
		}

		cout << " |";
	}
	cout << endl;
}

void Board::draw() const {
	drawFirstRow();
	drawCompleteLine();
	for (int i=0; i<m_boardSize ; i++) {
		drawRow(i);
		drawCompleteLine();
	}
}

