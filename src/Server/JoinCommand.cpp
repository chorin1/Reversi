//
// Created by chorin on 12/24/17.
//

#include <map>
#include <string>
#include <vector>
#include "JoinCommand.h"
#include "GameList.h"

void JoinCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	std::vector<std::string> msgVec;

	pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	std::map<std::string, GameSession*>::iterator it = GameList::getInstance().gameSessionMap.find(args.at(1));
	// if game doesnt exist
	if (it == GameList::getInstance().gameSessionMap.end()) {
		msgVec.push_back("not exist");
		m_server->sendSerialized(senderSocket, msgVec);
		m_server->closeSocket(senderSocket);
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

		// thread will handleSession until game ends
		m_server->HandleSession(p1socket, senderSocket);
	} catch (const char* msg) {
		handleErr(msg);
	}
}