/*
 *  Reversi - Advanced Programming 1
 *  Ex: #2
 *	Group: 04
 *  Author: Ben Chorin
 *  ID: 021906185
 *  Date: 12/11/17
 */

#include "GameModel.h"
#include "ConsoleView.h"
#include "HumanPlayer.h"
#include "Controller.h"
#include "AIPlayer.h"
#include <iostream>
#include <cstdlib>


using std::cin;
using std::cout;
using std::endl;

int getMenuChoice();

int main() {

	cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
	cout << "------------------------------------------" << endl << endl;
	cout << "Please select form the following options:" << endl;
	cout << "1. Play against a human player." << endl;
	cout << "2. Play against an AI player." << endl << endl;
	cout << "choice: ";

    int choice = getMenuChoice();

	switch (choice) {
		case 1: {
            cout << "Starting a PVP game..." << endl;
			GameModel model(4);
			ConsoleView view(model);
			HumanPlayer p1;
			HumanPlayer p2;
			Controller controller(model, view, p1, p2);
			controller.beginGame();
			break;
		}
		case 2:
		default: {
            cout << "Starting a Player VS Computer game..." << endl;
			GameModel model(4);
			ConsoleView view(model);
			HumanPlayer p1;
			AIPlayer p2;
			Controller controller(model, view, p1, p2);
			controller.beginGame();
			break;
		}
	}


	std::cin.get();
    return 0;
}

int getMenuChoice() {
	std::string input;
	while (true) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid choice. Please try again: ";
		} else {
			std::cin.ignore(32767, '\n');
			if (input.length()==1 && ((input.find('1')!=std::string::npos || input.find('2')!=std::string::npos))) {
				return atoi(input.c_str());
			}

			else
				cout << "Invalid choice. Please try again: ";
		}

	}
}


