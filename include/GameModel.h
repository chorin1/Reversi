/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  GameModel is responsible to store the data of the Reversi game. (eg. the board, possible moves for each player)
*  Also responsible to store game logic (eg. what is a possible move)
*  Has a position struct used to describe a point on the board.
*/

#pragma once
#include "Board.h"
#include <vector>

class GameModel {
	friend class AIPlayerTest;
	friend class GameModelTest;
public:

	struct Pos {
		int m_x;
		int m_y;
        Pos (int x,int y): m_x(x), m_y(y) {}
		//copy constructor
		Pos (const Pos& other): m_x(other.m_x), m_y(other.m_y) {}
		
		bool operator==(const Pos& pos2) const {
			return pos2.m_x == m_x && pos2.m_y == m_y;
		}
		bool operator!=(const Pos& pos2) const {
			return !(*this == pos2);
		}
	};

	enum PlayerNum {
		PLAYER1,
		PLAYER2
	};

	const static int DEFAULT_BOARD_SIZE = 8;
	const static int MAX_BOARD_SIZE = Board::MAX_BOARD_SIZE;

	//create with default boardSize
	GameModel();
	//create with custom boardSize
	GameModel(int boardSize);
	//copy constructor (copies the whole board and the player's possible moves)
	GameModel(const GameModel &otherModel);
	~GameModel();
	
	//place a piece of player in a position. return true if succeeded.
	bool place (const PlayerNum& player, const Pos& pos); 
	//returns a read-only pointer to the possibleMoves vector of a certain player
	const std::vector<Pos>* getPossibleMoves(PlayerNum player) const;
	bool isAbleToMove(const PlayerNum& player) const;
	//return whats on the cell at a specific position 
	Board::Cell getCellAt(const Pos& pos) const; 
	int getBoardSize() const {return this->m_board->getBoardSize();}

	//update the possible moves
	void updatePossibleMoves(PlayerNum player); 
	bool isPossibleMove(const PlayerNum& player, const Pos& pos) const;

	//use to calculate score at end of game. scoreP1 and scoreP2 will be overwritten with the resulting score of each player.
	int calcScoreOf(PlayerNum player) const;

private:
	Board* m_board;
	std::vector<Pos> m_possibleMovesPlayer1;
	std::vector<Pos> m_possibleMovesPlayer2;

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

	// recursive handle method to check if a certain move is possible in a certain direction.
	//return true if the move at that direction is possible.
	//if doFlip is set to true then it will flip the opponent pieces (only if move is valid).
	//found is a handle parameter, init always with false.
	bool goTo(const Direction& direction, const Board::Cell& currPlayerPiece, const Pos& pos, const bool& doFlip, bool found);

	//is position out of board bounds
	bool isOutOfBounds (const Pos& pos) const;
	void setCellAt(const Pos& pos, const Board::Cell piece);

	//flip the piece at position X->O, O->x
	void flip(const Pos& pos);
};

