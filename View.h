#pragma once
#include "GameModel.h"
//interface for view

class View {
public:
	View() {};
	virtual ~View() {}
	virtual void DrawBoard() const =0;
	virtual void drawPossibleMoves (const std::vector<GameModel::Pos> possVector) const =0;
	virtual void askForInputfromPlayer(GameModel::PlayerNum currPlayer) const = 0;
};