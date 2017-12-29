/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  Main menu for the Reversi game.
*  Shows the menu in the console and creates the game (controller, players and model)
*  according to the user choice. will also init a networked game with assist of class Client.
*/

#pragma once

#include "Client.h"
#include "Player.h"
#include "ConsoleView.h"

class GameMaker {
public:
	GameMaker() : p1(NULL), p2(NULL), client(NULL) {}
	enum GameType {
        PVP = 1,
		PVC,
		NETWORK_GAME,
		GAME_TYPE_EXIT,
		GAMETYPE_COUNT
	};
	enum NetMenuOptions {
		JOIN = 1,
		CREATE,
		LIST,
		NET_MENU_EXIT,
		NETMENUOPTIONS_COUNT
	};
	GameType m_choice;
	void mainMenuSelection();
	void beginGame();
private:
	Player *p1;
	Player *p2;
	Client *client;
	void getMainMenuChoice();
	NetMenuOptions getNetworkMenuChoice();

	// set up client and create a NetPlayer.
	void makeNetworkGamePlayers();

	// print current game sessions from server
	void printCurrentGameSessions();
	// show the networked game sub-menu
	void showNetSubMenu();
	// get from user game name to join or create
	std::string getDesiredGameNameFromUser();
};