/*
 * main.cpp
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 *  ID: 021906185
 */
#include "Board.h"
//#include "GameModel.h"
//#include "ConsoleView.h"
//#include "Controller.h"
//#include "HumanPlayer.h"

int main() {
	/*
	GameModel model;
	ConsoleView view (model);
	HumanPlayer hplayer1;
	HumanPlayer hplayer2;
	Controller controller(model, view, hplayer1, hplayer2);
	controller.beginGame();
	*/
	Board* board = new Board(8);
	board->draw();
}



