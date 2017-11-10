/*
 * main.cpp
 *
 *  Created on: Oct 25, 2017
 *  Author: Ben Chorin
 *  ID: 021906185
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
	HumanPlayer dude;
	HumanPlayer dad;
	Controller controller(model, view, dude, dad);
	controller.beginGame();


	std::cin.get();
    return 0;
}



