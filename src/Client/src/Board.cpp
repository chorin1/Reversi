/*
 * Board.cpp
 *
 *  Created on: Oct 25, 2017
 *
 */

#include "../include/Board.h"
#include <assert.h>

Board::Board(int boardSize = DEFAULT_BOARD_SIZE): m_boardSize(boardSize) {
	m_board = new Cell [m_boardSize * m_boardSize];
	initBoard();
}

Board::Board(const Board &otherBoard): m_boardSize(otherBoard.m_boardSize) {
	m_board = new Cell[m_boardSize * m_boardSize];
	for (int i = 0; i < Board::m_boardSize; i++) {
		for (int j = 0; j < Board::m_boardSize; j++) {
			Board::setCellValue(i, j, otherBoard.getCellAt(i,j));
		}
	}
}

Board::~Board() {
	delete[] m_board;
}

void Board::initBoard() {
	assert(Board::m_boardSize > 3 || Board::m_boardSize < MAX_BOARD_SIZE);
        int center = Board::m_boardSize / 2;
        for (int i = 0; i < Board::m_boardSize; i++) {
            for (int j = 0; j < Board::m_boardSize; j++) {
				if ((j == center - 1 && i == center - 1) || (j == center && i == center))
					Board::setCellValue(i, j, Board::CELL_PLAYER2);
                else if ((j == center - 1 && i == center) || (j == center && i == center - 1))
					Board::setCellValue(i, j, Board::CELL_PLAYER1);
                else
					Board::setCellValue(i, j, Board::CELL_EMPTY);
            }
        }
}
