#pragma once
#include "PlayerType.h"
#include "GameModel.h"

class HumanPlayer : public PlayerType {
public:
	HumanPlayer();
	~HumanPlayer();
	GameModel::Pos makeMove();
};