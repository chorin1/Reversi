#pragma once
#include "View.h"
#include "GameModel.h"

class ConsoleView : public View {
public:
	ConsoleView (const GameModel& model);
	~ConsoleView();
	void DrawBoard() const;
	void drawPossibleMoves (const std::vector<GameModel::Pos> possVector) const;
	void askForInputfromPlayer(GameModel::PlayerNum currPlayer) const;
};