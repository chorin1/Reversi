#pragma once
#include "Board.h"
#include <vector>


//PLAYER1 = X
//PLAYER2 = Y
class GameModel {
public:
	struct Pos {
		int x;
		int y;
		bool operator==(const Pos& pos2) const {
			return pos2.x == x && pos2.y == y;
		}
	};
	enum PlayerNum {
		PLAYER1,
		PLAYER2
	};

	GameModel();
	~GameModel();

	bool place (const PlayerNum& player, const Pos& pos);  //return true if move succedded
	void updatePossibleMoves(PlayerNum player); //run all across and update the possible moves vector
	bool isPossibleMove (const PlayerNum player, const Pos& pos) const;
	const std::vector<Pos> getPossibleMoves(PlayerNum player) const;
	bool isAbleToMove(PlayerNum player) const;
	const Board& getBoard() const; //returns the board as read-only (for viewing purposes)
	
private:
	Board board;
	std::vector<Pos> possibleMovesPlayer1;
	std::vector<Pos> possibleMovesPlayer2;
};

