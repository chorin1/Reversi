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
#include "GameModel.h"
#include "ConsoleView.h"
#include <iostream>
int main() {
	/*
	GameModel model;
	ConsoleView view (model);
	HumanPlayer hplayer1;
	HumanPlayer hplayer2;
	Controller controller(model, view, hplayer1, hplayer2);
	controller.beginGame();
	*/
	//Board* board = new Board(8);
	//board->draw();

    GameModel model;
    ConsoleView view(model);

    view.DrawBoard();
    GameModel::PlayerNum player1 = GameModel::PLAYER1;
    model.updatePossibleMoves(player1);
    view.drawPossibleMoves(player1);
    //std::cout << std::endl << "goto: " << model.goTo(GameModel::SE, Board::CELL_PLAYER1, GameModel::Pos(4, 4), false, false);
    //std::cout << "is able to move: " << model.isAbleToMove(player1);
    std::cout << std::endl;
    model.place(player1, GameModel::Pos(4,3));
    view.DrawBoard();
    model.updatePossibleMoves(player1);
    view.drawPossibleMoves(player1);
    std::cout << std::endl;
    model.place(player1, GameModel::Pos(6,6));
    view.DrawBoard();
    model.updatePossibleMoves(player1);
    view.drawPossibleMoves(player1);
	std::cin.get();
    return 0;
}



