#pragma once
#include "Board.h"
#include <vector>
#include <iostream>

class GameModel {
public:
	struct Pos {
		int m_x;
		int m_y;
        Pos (int x,int y): m_x(x), m_y(y) {}
        Pos (const Pos& other): m_x(other.m_x), m_y(other.m_y) {} //copy constructor
		bool operator==(const Pos& pos2) const {
			return pos2.m_x == m_x && pos2.m_y == m_y;
		}
	};
	enum PlayerNum {
		PLAYER1,
		PLAYER2
	};

	GameModel();
	~GameModel();
    // move to private later!!
    enum Direction {
        NORTH,
        SOUTH,
        WEST,
        EAST,
        NW,
        NE,
        SE,
        SW
    };

    void updatePossibleMoves(PlayerNum& player); //run all across and update the possible moves vector

    bool goTo (const Direction& direction, const Board::Cell& currPlayerPiece, const Pos& pos, const bool& doFlip, bool found);

    // end move to private

	bool place (const PlayerNum& player, const Pos& pos);  //return true if move succeeded
	const std::vector<Pos>* getPossibleMoves(PlayerNum player) const;
    bool isAbleToMove(PlayerNum& player) const;
	Board::Cell getCellAt(const Pos& pos) const;  //think about making private method and friend of view
    int getBoardSize() const {return this->m_board->getBoardSize();}

private:
	Board* m_board;
	std::vector<Pos> m_possibleMovesPlayer1;
	std::vector<Pos> m_possibleMovesPlayer2;
    const static int DEFAULT_BOARD_SIZE = 8;



    bool isPossibleMove (const PlayerNum& player, const Pos& pos) const;
    bool isOutOfBounds (const Pos& pos) const;
    void setCellAt(const Pos& pos, const Board::Cell piece); //void setCellValue(int x, int y, const Cell cell)
    //bool goDown(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found);
    //bool goUp(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found);
    //bool goLeft(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found);
    //bool goRight(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found);
    void flip(const Pos& pos);

};

