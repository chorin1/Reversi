/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Human player with input through keyboard.
*  the class is responsible to return a "sane" position back to the controller
*/

#pragma once
#include "Player.h"
#include "GameModel.h"
#include <iostream>

class HumanPlayer : public Player {
public:
	HumanPlayer() {}
	~HumanPlayer() {}
	GameModel::Pos makeMove(const GameModel* const = NULL) const;
};