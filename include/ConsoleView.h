/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  View class to play Reversi game on the console
*/

#pragma once
#include "View.h"
#include "GameModel.h"

class ConsoleView : public View {
public:

	//Explanation for the public methods can be read inside base class (view.h)
	ConsoleView (GameModel& model) : View(model){}
	~ConsoleView() {};
	void drawBoard() const;
	void drawTurn(const GameModel::PlayerNum player, const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const; 
	void drawNoPossibleMoves(const GameModel::PlayerNum player,
                             const GameModel::Pos lastPlacePos = GameModel::Pos(0, 0)) const;
	void drawNoPossibleMoveForBoth() const;
	void drawMoveIsInvalid(const GameModel::Pos& pos) const;
	void drawEndGame(int& scoreP1, int& scoreP2) const;
	void printException(const char* msg) const;
private:

	//draws the first row of the board (column numbering)
	void drawFirstRow() const; 
	//draws a complete separation line "---"
	void drawCompleteLine() const; 
	//draws a single row
	void drawRow(int row) const;
	//draws the player's possible moves (under the assumption that he can move)
	void drawPossibleMoves(const GameModel::PlayerNum ofPlayer) const; 
	//handle method - print a pos in the console
	void drawPos(const GameModel::Pos& pos) const;
};