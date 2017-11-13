/*
 * Board.cpp
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 */

#include "Board.h"
#include <iostream>
using namespace std;


Board::Board(int boardSize = 8): m_boardSize(boardSize) {
	m_board = new Piece*[m_boardSize];
		for (int i = 0; i < m_boardSize; ++i)
			m_board[i] = new Piece[m_boardSize];
	initBoard();

}

void Board::initBoard() {
    try {
        if (Board::m_boardSize < 3 || Board::m_boardSize > 20)
            throw 1;
        int center = Board::m_boardSize / 2;
        for (int i = 0; i < Board::m_boardSize; i++) {
            for (int j = 0; j < Board::m_boardSize; j++) {
                if ((j == center - 1 && i == center - 1) || (j == center && i == center))
                    Board::m_board[i][j] = Board::PIECE_O;
                else if ((j == center - 1 && i == center) || (j == center && i == center - 1))
                    Board::m_board[i][j] = Board::PIECE_X;
                else
                    Board::m_board[i][j] = Board::PIECE_EMPTY;
            }
        }
    }
    catch (int errorNum){
        if (errorNum==1)
            cout << endl << "Error #1, failed to initialize board, size invalid" <<endl;
    }
}

Board::~Board() {
	for(int i = 0; i < Board::m_boardSize; ++i) {
	  delete [] m_board[i];
	}
	delete [] m_board;
}

void Board::drawFirstRow() const {
	cout << " |";
	for (int i=1; i<= Board::m_boardSize; i++) {
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

		switch (Board::m_board[row][i]) {
		case Board::PIECE_EMPTY:
			cout << " ";
			break;
		case Board::PIECE_X:
			cout << "X";
			break;
		case Board::PIECE_O:
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

int Board::getBoardSize() const {
    return m_boardSize;
}

void Board::draw() const {
	drawFirstRow();
	drawCompleteLine();
	for (int i=0; i<Board::m_boardSize ; i++) {
		drawRow(i);
		drawCompleteLine();
	}
}

