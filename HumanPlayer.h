#pragma once
#include "Player.h"
#include "GameModel.h"

class HumanPlayer : public Player {
public:
	HumanPlayer() {}
	~HumanPlayer() {}
	GameModel::Pos makeMove() const;
};