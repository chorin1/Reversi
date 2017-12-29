/*
*  StartCommand.cpp
*
*/

#include <map>
#include <string>
#include <vector>
#include "../include/StartCommand.h"
#include "../include/GameList.h"
#include "../include/GameSession.h"

void StartCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	// check if game exists
	pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	if (GameList::getInstance().gameSessionMap.count(args.at(1)) > 0) {
		std::vector<std::string> msgVec;
		msgVec.push_back("exists");
		m_server->sendSerialized(senderSocket, msgVec);
		m_server->closeSocket(senderSocket);
		pthread_mutex_unlock(&GameList::getInstance().gameListMutex);
		return;
	}
	//add game to gamelist with with player1 socket
	GameList::getInstance().gameSessionMap[args.at(1)] = new GameSession(senderSocket);
	pthread_mutex_unlock(&GameList::getInstance().gameListMutex);
	std::cout << "game " << args.at(1) << " created" << std::endl;
	// socket REMAINS OPEN so another player can join
}