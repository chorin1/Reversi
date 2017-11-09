#pragma once
#include "View.h"
#include "GameModel.h"

class ConsoleView : public View {
public:
    ConsoleView (GameModel& model) : View(model){}
	~ConsoleView() {};
	void DrawBoard() const;
	void drawPossibleMoves (const GameModel::PlayerNum ofPlayer) const;
	//void askPlayerMove(GameModel::PlayerNum currPlayer) const;
private:
	void drawFirstRow() const; //draw the first row of the board (column numbering)
	void drawCompleteLine() const; //draw a complete separation line "---"
	void drawRow(int row) const; //draw a single row
};