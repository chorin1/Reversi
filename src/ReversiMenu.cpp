/*
*  ReversiMenu.cpp
*
*/

#include "../include/ReversiMenu.h"
#include "../include/GameModel.h"
#include "../include/Player.h"
#include "../include/HumanPlayer.h"
#include "../include/AIPlayer.h"
#include "../include/Controller.h"
#include "../include/ConsoleView.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

//must set static members globally
ReversiMenu::GameType ReversiMenu::m_choice = PVP;

void ReversiMenu::beginGame() {
	if (m_choice == 0) {
		cout << "Thank you for playing..." << endl;
	} else {
		GameModel model;
		ConsoleView view(model);
		Player *p1;
		Player *p2;
		switch (m_choice) {
			case PVC:
				p1 = new HumanPlayer();
				p2 = new AIPlayer();
				cout << "Starting a game vs AI..." << endl << endl;
			break;
			case PVP:
				p1 = new HumanPlayer();
				p2 = new HumanPlayer();
				cout << "Starting a PVP game..." << endl << endl;
			break;
			case NETWORK_GAME:
                //create client
                //connect to server
                //get player number
                //create a player with a reference to client
                //create a human player
                break;
			default:
				cout << "error in menu selection" << endl;

		}
		Controller controller(model, view, *p1, *p2);
		controller.beginGame();
		delete p1;
		delete p2;
	}
}

void ReversiMenu::selectFromMenu() {
	cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
	cout << "         -A Game By Nathan & Ben-     " << endl;
	cout << "------------------------------------------" << endl << endl;
	cout << "Please select form the following options:" << endl;
	cout << "1. Play against a human player." << endl;
	cout << "2. Play against an AI player." << endl;
	cout << "3. Play against a player on the network" << endl;
	cout << "0. Exit" << endl << endl;
	cout << "choice: ";

	m_choice = getMenuChoice();

}

ReversiMenu::GameType ReversiMenu::getMenuChoice() {
	int input;
	while (true) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid choice. Please try again: ";
		} else {
			std::cin.ignore(32767, '\n');
			if (input >= 0 && input < GAMETYPE_COUNT) {
				return static_cast<ReversiMenu::GameType>(input);
			} else
				cout << "Invalid choice. Please try again: ";
		}

	}
}