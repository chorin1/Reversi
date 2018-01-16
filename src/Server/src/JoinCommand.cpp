/*
*  JoinCommand.cpp
*
*/

#include <map>
#include <string>
#include <vector>
#include "../include/JoinCommand.h"
#include "../include/GameList.h"

void JoinCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	std::vector<std::string> msgVec;

	pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	std::map<std::string, GameSession*> &gameMap = GameList::getInstance().gameSessionMap;
	std::map<std::string, GameSession*>::iterator it = gameMap.find(args.at(1));
	// if game doesnt exist
	if (it == gameMap.end()) {
		pthread_mutex_unlock(&GameList::getInstance().gameListMutex);
		msgVec.push_back("notexist");
		try {
			m_server->sendSerialized(senderSocket, msgVec);
			m_server->closeSocket(senderSocket);
		} catch (const char* msg) {
			handleErr(msg);
		}
		return;
	}

	// game exists!, update game list
	it->second->player2Socket = senderSocket;
	// a temp object is created to release mutex quickly (without waiting messages to be sent to clients)
	int p1socket = it->second->player1Socket;

	pthread_mutex_unlock(&GameList::getInstance().gameListMutex);

	//send each client its role
	try {
		msgVec.push_back("player1");
		m_server->sendSerialized(p1socket, msgVec);

		msgVec.clear();
		msgVec.push_back("player2");
		m_server->sendSerialized(senderSocket, msgVec);

		std::cout << "session \"" << args.at(1) << "\" has started" << std::endl;

		// start a new session.
		m_server->newSession(p1socket, senderSocket);
	} catch (const char* msg) {
		handleErr(msg);
	}
}