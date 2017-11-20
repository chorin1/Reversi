/*
*  Reversi - Advanced Programming 1
*  Ex: #2
*  Group: 04
*  Author: Ben
*  Controller class for Reversi game - controls the game flow.
*  Responsible to tell the view what to show (and when).
*  Responsible to update the model according to game progression.
*/

#pragma once
#include "GameModel.h"
#include "View.h"
#include "Player.h"

class Controller {
	
public:
	//bind to controller to a model and a view. Assigned player paramater order sets who will be X and who O.
	Controller(GameModel& model, const View& view, const Player& player1, const Player& player2) :
		       m_model(&model), m_view(&view), m_player1(&player1), m_player2(&player2), gameEnded (false) , currentPlayerNum(GameModel::PLAYER1){}
	~Controller() {}
	void beginGame();

private:
    	//maybe later on think about making players and view not const (to be able to switch players and views mid-game)
	const View* const m_view;
	GameModel* const m_model;
	const Player* const m_player1;
	const Player* const m_player2;
	//stores who is currently playing (player 1 or 2)
	GameModel::PlayerNum currentPlayerNum;
	//has game ended?
	bool gameEnded;

	void switchCurrentPlayer();
	const Player* getCurrentPlayer() const;
};