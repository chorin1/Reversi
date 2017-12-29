/*
*  GameList.cpp
*
*/

#include "../include/GameList.h"

GameList::~GameList() {
	std::map<std::string, GameSession*>::iterator it;
	for (it = gameSessionMap.begin(); it != gameSessionMap.end(); it++) {
		delete it->second;
	}
}

GameList::GameList() {
	pthread_mutex_init(&gameListMutex, NULL);
}