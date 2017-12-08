/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  A basic class for creating board size NxN for Reversi
*/

#pragma once

class Board {
public:
	//enumeration of each cell data
	enum Cell {
		CELL_ERROR,
		CELL_EMPTY,
		CELL_PLAYER1,
		CELL_PLAYER2
	};

	//create a board according to boardSize
	Board(int boardSize);
	//Copy constructor
	Board(const Board &otherBoard);
	~Board();

	const static int DEFAULT_BOARD_SIZE = 8;
	const static int MAX_BOARD_SIZE = 30;
	int getBoardSize() const {return m_boardSize;}
	//returns the cell at location (converts the boardSize*boardSize to a 2d array)
	Cell getCellAt(int x, int y) const {return m_board[x + y*m_boardSize];}
	void setCellValue(int x, int y, const Cell cell) { m_board[x + y*m_boardSize] = cell; }

private:
	const int m_boardSize;
	Cell* m_board;
	//initialize the board according to Reversi starting positions
	void initBoard();
};
