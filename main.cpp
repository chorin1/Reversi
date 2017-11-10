/*
 *  Reversi - Advaced Programming 1
 *  Ex: #2
 *	Group: 04
 *  Author: Ben Chorin
 *  ID: 021906185
 *  Date: 12/11/17
 */

#include "Board.h"
#include "GameModel.h"
#include "ConsoleView.h"
#include "View.h"
#include "HumanPlayer.h"
#include "Controller.h"
#include <iostream>
int main() {

	GameModel model;
	ConsoleView view(model);
	HumanPlayer p1;
	HumanPlayer p2;
	Controller controller(model, view, p1, p2);
	controller.beginGame();


	std::cin.get();
    return 0;
}



