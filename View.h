#pragma once
#include "GameModel.h"
//interface for view

class View {
public:
	View(GameModel& model) {m_model = &model;};
	virtual ~View() {}
	virtual void DrawBoard() const =0;
	virtual void drawPossibleMoves (const GameModel::PlayerNum ofPlayer) const =0;
	//virtual void askPlayerMove(GameModel::PlayerNum currPlayer) const = 0;
protected:
	GameModel* m_model;
};