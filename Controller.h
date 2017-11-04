#pragma once
#include "GameModel.h"
#include "View.h"

class Controller {
	
	
public:

	Controller (GameModel& model, View& view, PlayerType& player1, PlayerType& player2);
	/*
		player1.playerNum = GameModel::PLAYER1
		player2.playerNum = GameModel::PLAYER2
	*/
	~Controller();
	void beginGame();
	/*

		view.drawBoard()
		currentplayer = playerX
		possMoves = getpossiblemoves(currentplayer)
		if (getpossiblemoves.notempty) {
			view.drawPossibleMoves(getpossiblemoves)
			wantedMovePos = playerX.makemove()
			model.isMovePossible?(watedMovePos)
			Place(Piece_X, wantedMovePos)
		
		}
	
	*/
	GameModel::PlayerNum playerNum = GameModel::PLAYER1;



};