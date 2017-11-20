/*
*  Reversi - Advanced Programming 1
*  Ex: #2
*  Group: 04
*  Interface class for view - use to draw Reversi game.
*/

#pragma once
#include "GameModel.h"

class View {
public:
	//on construction - bind the view to the model for board drawing purposes (read-only)
	View(GameModel& model) : m_model(&model) {}
	virtual ~View() {}

	virtual void drawBoard() const = 0;
	//show the last move and ask the current player to make a move. the method assumes the player CAN move.
	virtual void drawTurn(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos) const = 0;
	//show the last move and print that the current player has no possible moves
	virtual void drawNoPossibleMoves(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos) const = 0;
	//selected move by current player is invalid
	virtual void drawMoveIsInvalid (const GameModel::Pos& pos) const = 0;
	//Endgame graphics. parameters represent the final score of each player.
	virtual void drawEndGame(int& scoreP1, int& scoreP2) const = 0;
protected:
	const GameModel* m_model;
};