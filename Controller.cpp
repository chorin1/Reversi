#include "Controller.h"

Controller::beginGame() {

	while (!gameEnded) {
		m_view->DrawBoard();

		
		if (!m_model->isAbleToMove(GameModel::PLAYER1) && !m_model->isAbleToMove(GameModel::PLAYER2)) {
			gameEnded = true;
			continue;
		}

		//TURN
		if (!m_model->isAbleToMove(currentPlayer))
			PassTurn();
		m_view->printPlayerTurn(currentPlayer);
		m_view->drawPossibleMoves(currentPlayer);

		m_view->drawPossibleMoves
		m_player1->makeMove();


	}
	/*view.drawBoard()
currentplayer = playerX
possMoves = getpossiblemoves(currentplayer)
if (getpossiblemoves.notempty) {
view.drawPossibleMoves(getpossiblemoves)
wantedMovePos = playerX.makemove()
model.isMovePossible?(watedMovePos)
Place(Piece_X, wantedMovePos)
*/

}