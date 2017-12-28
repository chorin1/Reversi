/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Main menu for game reversi.
*  Shows the menu in the console and creates the game (controller, players and model)
*  according to the user choice.
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
	// get reference to client and player pointers. set up client and create network player.
	void makeNetworkGamePlayers();
	void printCurrentGameSessions();
	void showNetSubMenu();

	std::string getDesiredGameNameFromUser();
};