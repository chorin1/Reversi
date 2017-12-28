/*
*  ReversiMenu.cpp
*
*/

#include "../include/GameMaker.h"
#include "../include/GameModel.h"
#include "../include/Player.h"
#include "../include/HumanPlayer.h"
#include "../include/AIPlayer.h"
#include "../include/Controller.h"
#include "../include/ConsoleView.h"
#include "../include/Client.h"
#include "../include/NetPlayer.h"
#include "../include/Logging.h"
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

void GameMaker::beginGame() {
	if (m_choice == GAME_TYPE_EXIT) {
		cout << "Thank you for playing..." << endl;
	} else {
		GameModel model(4);
		ConsoleView view(model);
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
				makeNetworkGamePlayers();
				break;
			default:
				cout << "error in menu selection" << endl;
				break;
		}
		if (p1!=NULL && p2!=NULL) {
			Controller controller(model, view, *p1, *p2);
			controller.beginGame();
			if (client!= NULL)
				try {
					client->closeSession();
				} catch (char const* msg) {}
			std::cin.ignore();
		}
		delete p1;
		delete p2;
		delete client;
		p1 = NULL;
		p2 = NULL;
		client = NULL;
	}
}

// get reference to client and player pointers. set up client and create players
void GameMaker::makeNetworkGamePlayers() {
	NetMenuOptions netMenuChoice;
	std::string netGameName;
	int clientPlayerNum = 0;
	try {
		client = new Client();
		cout << "Connecting to " << client->getServerIP() << ":" << client->getServerPort() << endl;
		client->connectToServer();
		cout << "Connected to server.." << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "|                  Network Game                  |" << endl;
		cout << "--------------------------------------------------" << endl << endl;
		printCurrentGameSessions();
		client->disconnect();
	} catch (const char *msg) {
		cout << msg << endl;
		cout << "Press any key to return to main menu.." << endl << endl;
		std::cin.ignore();
		return;
	}

	do {
		showNetSubMenu();
		netMenuChoice = getNetworkMenuChoice();
		try {
			switch (netMenuChoice) {
				case JOIN:
					netGameName = getDesiredGameNameFromUser();
					client->connectToServer();
					clientPlayerNum = client->joinGame(netGameName);
					break;
				case CREATE:
					netGameName = getDesiredGameNameFromUser();
					client->connectToServer();
					clientPlayerNum = client->createGame(netGameName);
					break;
				case LIST:
					client->connectToServer();
					printCurrentGameSessions();
					client->disconnect();
					break;
				case NET_MENU_EXIT:
                    delete (client);
                    client = NULL;
					return;
				default:
                    throw "error in menu selection";
					break;
			}
		} catch (const char *errMsg) {
			cout << errMsg << endl;
		}
	} while (clientPlayerNum==0);

	client->setSessionName(netGameName);
	if (clientPlayerNum==1) {
		p1 = new HumanPlayer();
		p2 = new NetPlayer(*client);
		cout << "Starting network Game - you will play as 'X'" << endl;
		cout << "Press enter to being.." << endl;
		std::cin.ignore();
	}
	else if (clientPlayerNum==2) {
		p1 = new NetPlayer(*client);
		p2 = new HumanPlayer();
		cout << "Starting network Game - you will play as 'O'" << endl;
		cout << "Press enter to being.." << endl;
		std::cin.ignore();
	} else {
		cout << "Error, didn't get player number from server..";
		p1 = NULL;
		p2 = NULL;
	}
}

void GameMaker::showNetSubMenu() {
	cout << "Please select from the following options:" << endl;
	cout << "1. Join game" << endl;
	cout << "2. Create game" << endl;
	cout << "3. Refresh list" << endl;
	cout << "4. Back to main menu" << endl << endl;
	cout << "choice: ";
}

void GameMaker::mainMenuSelection() {
	cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
	cout << "         -A Game By Nitai & Ben-     " << endl;
	cout << "------------------------------------------" << endl << endl;
	cout << "Please select form the following options:" << endl;
	cout << "1. Play against a human player." << endl;
	cout << "2. Play against an AI player." << endl;
	cout << "3. Play against a player on the network" << endl;
	cout << "4. Exit" << endl << endl;
	cout << "choice: ";

	getMainMenuChoice();
}

void GameMaker::getMainMenuChoice() {
	std::string input;
	while (true) {
		getline(cin, input);
		int value = atoi(input.c_str());
		if (value > 0 && value < GAMETYPE_COUNT) {
			m_choice = static_cast<GameType>(value);
			return;
		} else
			cout << "Invalid choice. Please try again: ";
	}
}

GameMaker::NetMenuOptions GameMaker::getNetworkMenuChoice() {
	std::string input;
	while (true) {
		getline(cin, input);
		int value = atoi(input.c_str());
		if (value > 0 && value < NETMENUOPTIONS_COUNT) {
			return static_cast<NetMenuOptions>(value);
		} else
			cout << "Invalid choice. Please try again: ";
	}
}

void GameMaker::printCurrentGameSessions() {
	std::vector<std::string> sessions;
	if (client == NULL)
		return;
	try {
		sessions = client->getOpenSessions();
	} catch (const char* msg) {
		throw;
	}
	if (sessions.at(0) == "empty") {
		cout << "There are currently no open games on the server." << endl << endl;
		return;
	}
	int i=1;
	cout << "Currently open sessions on the server:" << endl;
	for(std::vector<std::string>::iterator it = sessions.begin(); it != sessions.end(); ++it) {
		cout << "\t#" << i << " " << *it << endl;
		i++;
	}
	cout << endl;
}

std::string GameMaker::getDesiredGameNameFromUser() {
	std::string name;
	cout << "Please enter game name: ";
	std::getline(std::cin, name);
	return name;
}