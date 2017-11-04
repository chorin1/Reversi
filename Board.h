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
        CELL_EMPTY,
        CELL_X,
        CELL_O
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
    int getBoardSize() const;

	Cell getCellAt(int x, int y) const;
	void setCellAt (int x, int y, Cell cell);

private:
	const int m_boardSize;
	Cell** m_board;

	void initBoard(); //initialize the board according to Reversi starting positions
	void drawFirstRow() const; //draw the first row of the board (column numbering)
	void drawCompleteLine() const; //draw a complete separation line "---"
	void drawRow(int row) const; //draw a single row

};