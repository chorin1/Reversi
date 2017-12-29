/*
*  CloseCommand.cpp
*
*/

#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include "../include/GameList.h"
#include "../include/CloseCommand.h"

void CloseCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	// delete game from gamelist
	std::map<std::string, GameSession*> &sessionMap = GameList::getInstance().gameSessionMap;
	std::map<std::string, GameSession*>::iterator it = sessionMap.find(args.at(1));
	if (it == sessionMap.end())
		std::cout << "socket #" << senderSocket << " is trying to close a non-existing game" << std::endl;
	else {
		std::cout << "closing game " << it->first << std::endl;
		delete (it->second);
		sessionMap.erase(it);
		std::cout << "closing socket #" << senderSocket << std::endl;
		close(senderSocket);
		std::cout << "closing socket #" << otherSocket << std::endl;
		close(otherSocket);
	}
	pthread_mutex_unlock(&GameList::getInstance().gameListMutex);
}