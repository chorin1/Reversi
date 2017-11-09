#pragma once
#include "GameModel.h"
#include "View.h"
#include "Player.h"

class Controller {
	
public:

	Controller(const GameModel& model, const View& view, const Player& player1, const Player& player2) :
		m_model(&model), m_view(&view), m_player1(&player1), m_player2(&player2), gameEnded (false) , currentPlayer(GameModel::PLAYER1){}
	~Controller() {}
	void beginGame();
	
private:
	const View* m_view;
	const GameModel* m_model;
	const Player* m_player1;
	const Player* m_player2;
	GameModel::PlayerNum currentPlayer;
	bool gameEnded;
};