/*
*  Reversi - Advanced Programming 1
*  Ex: #2
*  Group: 04
*  Author: Ben
*  Human player with input through keyboard.
*  the class is responsible to return a "sane" position back to the controller
*/

#pragma once
#include "Player.h"
#include "GameModel.h"

class HumanPlayer : public Player {
public:
	HumanPlayer() {}
	~HumanPlayer() {}
	GameModel::Pos makeMove() const;
};