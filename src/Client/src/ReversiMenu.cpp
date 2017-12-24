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
#include "../include/Client.h"
#include "../include/NetPlayer.h"
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
		GameModel model(4);
		ConsoleView view(model);
		Player *p1 = NULL;
		Player *p2 = NULL;
		Client *client = NULL;
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
				makeNetworkGamePlayers(client,p1,p2);
				break;
			default:
				cout << "error in menu selection" << endl;
				break;
		}
		if (p1!=NULL && p2!=NULL) {
			Controller controller(model, view, *p1, *p2);
			controller.beginGame();
		}
		delete p1;
		delete p2;
		delete client;
	}
}

// get reference to client and player pointers. set up client and create players
void ReversiMenu::makeNetworkGamePlayers(Client* &client, Player* &p1, Player* &p2) {
	try {
		// create a client with config file
		client = new Client();
		client->connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		return;
	}
	cout << "Connected to server!" << endl;
	//TODO: show netsubmenu

	int clientPlayerNum = netSubMenu(client);

	//cout << "Waiting for other players to join..." << endl;
	//int clientPlayerNum = client->getClientPlayerNum();
	//cout << "Another player joined..." << endl << endl;
	if (clientPlayerNum == 1) {
		cout << "Another player joined..." << endl << endl;
		p1 = new HumanPlayer();
		p2 = new NetPlayer(*client);
		cout << "You will play as 'X'" << endl;
	} else {
		p1 = new NetPlayer(*client);
		p2 = new HumanPlayer();
		cout << "You will play as 'O'" << endl;
	}
	cout << "Starting a network game..." << endl << endl;
}

//TODO add gameListObject <-- start here

int ReversiMenu::netSubMenu(Client* &client) {
	cout << "------------------------------------------" << endl;
	cout << "                Network Game              " << endl;
	cout << "------------------------------------------" << endl << endl;

	//TODO: print all game sessions
 	int numberOfGames = client->numberOfGames();
	if(numberOfGames == 0){
		cout << "nobody wait for game you can create game or wait more and do refresh" << endl;
	}
	else{
		cout << "Current game sessions:" << endl;
		std::vector <std::string> nameOfGames = client->receiveSerialized();
		//print the list of the games
		for (int i = 1; i <= numberOfGames; i++){
			cout << i << "." << nameOfGames[i] << endl;
		}
	}
	cout << endl << endl;
	cout << "Please select form the following options:" << endl;
	cout << "1. Join game" << endl;
	cout << "2. Create game" << endl;
	cout << "3. Refresh list" << endl;
	cout << "0. return to main menu" << endl << endl;


	int netMenuChoice;
	while (true) {
		cin >> netMenuChoice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid choice. Please try again: ";
		} else {
			std::cin.ignore(32767, '\n');
			if (netMenuChoice >= 0 && netMenuChoice <= 3) {
				break;
			} else
				cout << "Invalid choice. Please try again: ";
		}
	}
	while(netMenuChoice == 3) {

		switch (netMenuChoice) {
			case 0:
				client->disconnect();
				selectFromMenu();
				break;
			case 1:
				//todo:magic number check if we need that
				client->numberOption(1);
				cout << "choose which game you want to join" << endl;
				int numberGameChoice;
				while (true) {
					cin >> numberGameChoice;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(32767, '\n');
						cout << "Invalid choice. Please try again: ";
					} else {
						std::cin.ignore(32767, '\n');
						if (numberGameChoice >= 1 && netMenuChoice <= numberOfGames) {
							break;
						} else
							cout << "Invalid choice. Please try again: ";
					}
				}
				client->numberOption(numberGameChoice);

				return 0;

				//break;
			case 2:
				//todo:magic number check if we need that
				client->numberOption(2);
				cout << "write the name of your game please " << endl;
				std::string nameGame;

				std::vector<std::string> namesGame;

				cin >> nameGame;

				namesGame.push_back(nameGame);

				client->sendSerialized(namesGame);
				cout << "Waiting for other players to join..." << endl;
				return 1;
				//break;
			case 3:
				client->numberOption(3);
				cout << "Current game sessions:" << endl;
				std::vector <std::string> nameOfGames = client->receiveSerialized();
				//print the list of the games
				for (int i = 1; i <= numberOfGames; i++)
					cout << i << "." << nameOfGames[i] << endl;
				cout << endl << endl;
				cout << "Please select form the following options:" << endl;
				cout << "1. Join game" << endl;
				cout << "2. Create game" << endl;
				cout << "3. Refresh list" << endl;
				cout << "0. return to main menu" << endl << endl;

				break;
			default:
				break;
		}
	}

}

void ReversiMenu::selectFromMenu() {
	cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
	cout << "         -A Game By Nitai & Ben-     " << endl;
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

