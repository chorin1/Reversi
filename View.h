#pragma once
#include "GameModel.h"
//interface for view

class View {
public:
	View(GameModel& model) : m_model(&model) {}
	virtual ~View() {}
	virtual void drawBoard() const = 0;
	virtual void drawTurn(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const = 0;
	virtual void drawNoPossibleMoves(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const = 0;
	virtual void drawMoveIsInvalid (GameModel::Pos& pos) const = 0;
	virtual void drawEndGame(int& scoreP1, int& scoreP2) const = 0;
protected:
	GameModel* m_model;
};