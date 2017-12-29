/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  a singletone class, stores all current game sessions.
*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include "GameSession.h"

class GameList {
public:
	static GameList& getInstance() {
		static GameList instance; // static singleton, guaranteed to be deleted
		return instance;
	}
	std::map <std::string, GameSession*> gameSessionMap;
	// mutex for preventing multiple threads accessing the session map at the same time
	pthread_mutex_t gameListMutex;
private:
	GameList();
	GameList(const GameList&) {} // Prevent construction by copying
	GameList& operator=(const GameList&) {} // Prevent assignment
	~GameList(); // Prevent unwanted destruction
};