/*
 * Board.h
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 *  ID: 021906185
 *  basic class for creating a board of size AxA
 */
#pragma once

class Board {

public:

    enum Cell {
        CELL_ERROR,
        CELL_EMPTY,
        CELL_PLAYER1,
        CELL_PLAYER2
    };

    /**
     * creates and initializes a board according to Reversi rules
     * @param boardSize the size of the board that will be created (valid sizes are 3..20, default is 8)
     */
	Board(int boardSize);
	~Board();
    /**
     * draws the current board state in the console
     */
	void draw() const;

    /**
     * @return the size of the board
     */
	int getBoardSize() const {return m_boardSize;}

	Cell getCellAt(int x, int y) const {return m_board[x + y*m_boardSize];}
	void setCellValue(int x, int y, const Cell cell) { m_board[x + y*m_boardSize] = cell; }

private:
	const int m_boardSize;
	Cell* m_board;

	void initBoard(); //initialize the board according to Reversi starting positions

};