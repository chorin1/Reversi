#pragma once
#include "GameModel.h"
#include "View.h"
#include "Player.h"

class Controller {
	
public:

	Controller(GameModel& model, const View& view, const Player& player1, const Player& player2) :
		m_model(&model), m_view(&view), m_player1(&player1), m_player2(&player2), gameEnded (false) , currentPlayerNum(GameModel::PLAYER1){}
	~Controller() {}
	void beginGame();
	
private:
	const View* const m_view;
	GameModel* const m_model;
	const Player* const m_player1;
	const Player* const m_player2;
	GameModel::PlayerNum currentPlayerNum;
	bool gameEnded;

	void switchCurrentPlayer();
	const Player* getCurretPlayer() const;
};