#pragma once
#include "GameModel.h"

class Player {
public:
	Player() {};
	virtual ~Player() {};
	virtual GameModel::Pos makeMove() const = 0;
};