/*
*  Controller.cpp
*
*/

#include "../include/Controller.h"
#include "../include/Client.h"

void Controller::beginGame() {
	GameModel::Pos lastMove = GameModel::Pos(0, 0);
	gameEnded = false;

	while (!gameEnded) {
		m_view->drawBoard();

		//both players can't move
		if (!m_model->isAbleToMove(GameModel::PLAYER1) && !m_model->isAbleToMove(GameModel::PLAYER2)) {
			gameEnded = true;
			m_view->drawNoPossibleMoveForBoth();
			continue;
		}

		//current player has no moves
		if (!m_model->isAbleToMove(currentPlayerNum)) {
			m_view->drawNoPossibleMoves(currentPlayerNum, lastMove);
			// zeroize the last move
			lastMove = GameModel::Pos(0, 0);
			switchCurrentPlayer();
			//send noMove to other player
			try {
				getCurrentPlayer()->sendMove(NO_MOVE_POS);
			} catch (const char *msg) {
				m_view->printException(msg);
			}
			continue;
		}
		
		//current player has moves

		//draw turn if this player is human
		if (isCurPlayerHuman) {
			m_view->drawTurn(currentPlayerNum, lastMove);
		}
		GameModel::Pos wantedMove(0,0);
		bool moveValid = false;
		//loop until player selects a valid move
		do {
			try {
				wantedMove = getCurrentPlayer()->makeMove(m_model);
			} catch (const char* msg){
				m_view->printException(msg);
				// if disconnected from server, the game will end
				gameEnded = true;
				break;
			}
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

		//send the move to network player
		try {
			getCurrentPlayer()->sendMove(lastMove);
		} catch (const char *msg){
			m_view->printException(msg);
			// if disconnected from server, the game will end
			gameEnded = true;
			continue;
		}
		//end of turn
	}

	//game has ended
	int score1 = m_model->calcScoreOf(GameModel::PLAYER1);
	int score2 = m_model->calcScoreOf(GameModel::PLAYER2);
	m_view->drawEndGame(score1, score2);
}

void Controller::switchCurrentPlayer() {
	currentPlayerNum = (currentPlayerNum == GameModel::PLAYER1)? GameModel::PLAYER2 : GameModel::PLAYER1;
	isCurPlayerHuman = (currentPlayerNum == GameModel::PLAYER1)? isPlayer1Human : isPlayer2Human;
}
const Player* Controller::getCurrentPlayer() const {
	return (currentPlayerNum == GameModel::PLAYER1) ? m_player1 : m_player2;
}