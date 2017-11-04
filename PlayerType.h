#pragma once
#include "GameModel.h"

class PlayerType {
public:
	PlayerType() {};
	virtual ~PlayerType() {};
	virtual GameModel::Pos makeMove() = 0;
	GameModel::PlayerNum playerNum;
};