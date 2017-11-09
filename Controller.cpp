#include "Controller.h"

void Controller::beginGame() {

	while (!gameEnded) {
		m_view->drawBoard();

		if (!m_model->isAbleToMove(GameModel::PLAYER1) && !m_model->isAbleToMove(GameModel::PLAYER2)) {
			gameEnded = true;
			continue;
		}

		if (!m_model->isAbleToMove(currentPlayerNum)) {
			m_view->drawNoPossibleMoves(currentPlayerNum);
			switchCurrentPlayer();
			continue;
		}
		
		m_view->drawTurn(currentPlayerNum);
		GameModel::Pos wantedMove(0,0);
		bool moveValid = false;
		do {
			wantedMove = getCurretPlayer()->makeMove();
			if (m_model->isPossibleMove(currentPlayerNum, wantedMove)) {
				moveValid = true;
			}
			else 
				m_view->drawMoveIsInvalid(wantedMove);			
		} while (!moveValid);

		//move is valid, lets place the piece
		m_model->place(currentPlayerNum, wantedMove);
		switchCurrentPlayer();
	}

	//game has ended
	int score1 = 0;
	int score2 = 0;
	m_model->calculateScore(score1, score2);
	m_view->drawEndGame(score1, score2);
}

void Controller::switchCurrentPlayer() {
	currentPlayerNum = (currentPlayerNum == GameModel::PLAYER1) ? GameModel::PLAYER2 : GameModel::PLAYER1;
}
const Player* Controller::getCurretPlayer() const {
	return (currentPlayerNum == GameModel::PLAYER1) ? m_player1 : m_player2;
}
