#pragma once
#include "View.h"
#include "GameModel.h"

class ConsoleView : public View {
public:
    ConsoleView (GameModel& model) : View(model){}
	~ConsoleView() {};
	void drawBoard() const;
	void drawTurn(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const; //No check if has a move
	void drawNoPossibleMoves(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const;
	void drawMoveIsInvalid(GameModel::Pos& pos) const;
	void drawEndGame(int& scoreP1, int& scoreP2) const;
private:
	void drawFirstRow() const; //draw the first row of the board (column numbering)
	void drawCompleteLine() const; //draw a complete separation line "---"
	void drawRow(int row) const; //draw a single row
	void drawPossibleMoves(const GameModel::PlayerNum ofPlayer) const; //draws the player's possible moves (under the assumption that he can move)
	void drawPos(const GameModel::Pos& pos) const;
};