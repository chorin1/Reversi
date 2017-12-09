/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Player interface for creating players (human, AI or LAN/WEB) to play game reversi.
*/


#pragma once
#include <iostream>
#include "GameModel.h"

class Player {
public:
	Player() {};
	virtual ~Player() {};
	/*
	 * return the position of the wanted move by the player
	 * sending the model is only implemented in AI players
	 */
	virtual GameModel::Pos makeMove(const GameModel* const = NULL) const = 0;
    //only implemented in a network player
    virtual void sendMove(GameModel::Pos) const {}
};