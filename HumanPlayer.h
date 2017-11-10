/*
*  Reversi - Advaced Programming 1
*  Ex: #2
*  Group: 04
*  Author: Ben Chorin
*  ID: 021906185
*  Human player with input through keyboard.
*  the class is resposible to return a "sain" position back to the controller
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