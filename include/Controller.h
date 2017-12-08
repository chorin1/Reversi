/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Controller class for Reversi game - controls the game flow.
*  Responsible to tell the view what to show (and when).
*  Responsible to update the model according to game progression.
*/

#pragma once
#include "GameModel.h"
#include "View.h"
#include "Player.h"
#include "HumanPlayer.h"

class Controller {
public:
	//bind controller to a model and a view. Player parameter order will define who will be X and who O.
	Controller (GameModel& model, const View& view, const Player& player1, const Player& player2) :
                m_model(&model), m_view(&view), m_player1(&player1), m_player2(&player2),
                gameEnded (false) , currentPlayerNum(GameModel::PLAYER1) {
		//if player is human, switch the human flag (for draw board and draw moves for player)
		if (const HumanPlayer* pcast1 = dynamic_cast<const HumanPlayer*>(m_player1))
			isPlayer1Human = true;
		else
			isPlayer1Human = false;
        if (const HumanPlayer* pcast2 = dynamic_cast<const HumanPlayer*>(m_player2))
            isPlayer2Human = true;
        else
            isPlayer2Human = false;

        isCurPlayerHuman = isPlayer1Human;
	}
	~Controller() {}
	void beginGame();

private:
	const View* const m_view;
	GameModel* const m_model;
	const Player* const m_player1;
	const Player* const m_player2;
	bool isPlayer1Human;
	bool isPlayer2Human;
	//stores who is currently playing (player 1 or 2)
	GameModel::PlayerNum currentPlayerNum;
	bool isCurPlayerHuman;
	//has game ended?
	bool gameEnded;

	void switchCurrentPlayer();
	const Player* getCurrentPlayer() const;
};