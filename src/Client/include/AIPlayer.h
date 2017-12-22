/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Date: 27/11/17
*  This class represents an AI playing Reversi game using the minimax algorithm.
*  The class assumes computer will always play 'O' (player 2)
*/

#pragma once
#include "Player.h"

class AIPlayer : public Player {
public:
	AIPlayer() {};
	~AIPlayer() {};
	//returns the position of the wanted move using minimax AI method
	GameModel::Pos makeMove(const GameModel* const model) const;
private:
	int maxOpponentMoveScore(const GameModel* const model) const;
};