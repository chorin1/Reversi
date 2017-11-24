/*
*  Controller.cpp
*
*/

#include "../include/Controller.h"

void Controller::beginGame() {
	GameModel::Pos lastMove = GameModel::Pos(0, 0);
    gameEnded = false;
	while (!gameEnded) {

		//both players can't move
		if (!m_model->isAbleToMove(GameModel::PLAYER1) && !m_model->isAbleToMove(GameModel::PLAYER2)) {
			m_view->drawBoard();
			gameEnded = true;
			continue;
		}

		//current player has no moves
		if (!m_model->isAbleToMove(currentPlayerNum)) {
			m_view->drawBoard();
			m_view->drawNoPossibleMoves(currentPlayerNum, lastMove);
			lastMove = GameModel::Pos(0, 0);
			switchCurrentPlayer();
			continue;
		}
		
		//current player has moves

		//draw board and turn if this player is human
		if (!(currentPlayerNum==GameModel::PLAYER2 && isPlayer2Human==false)) {
			m_view->drawBoard();
			m_view->drawTurn(currentPlayerNum, lastMove);
		}
		GameModel::Pos wantedMove(0,0);
		bool moveValid = false;
		//loop until player selects a valid move
		do {
			wantedMove = getCurrentPlayer()->makeMove(m_model);
			if (m_model->isPossibleMove(currentPlayerNum, wantedMove)) {
				moveValid = true;
			}
			else 
				m_view->drawMoveIsInvalid(wantedMove);			
		} while (!moveValid);

		//move is valid, lets place the piece
		m_model->place(currentPlayerNum, wantedMove);
		lastMove = wantedMove;
		switchCurrentPlayer();
	}

	//game has ended
	int score1 = m_model->calcScoreOf(GameModel::PLAYER1);
	int score2 = m_model->calcScoreOf(GameModel::PLAYER2);
	m_view->drawEndGame(score1, score2);
}

void Controller::switchCurrentPlayer() {
	currentPlayerNum = (currentPlayerNum == GameModel::PLAYER1) ? GameModel::PLAYER2 : GameModel::PLAYER1;
}
const Player* Controller::getCurrentPlayer() const {
	return (currentPlayerNum == GameModel::PLAYER1) ? m_player1 : m_player2;
}
