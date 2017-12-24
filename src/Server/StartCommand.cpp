//
// Created by chorin on 12/24/17.
//

#include <map>
#include <string>
#include <vector>
#include "StartCommand.h"
#include "GameSession.h"

void StartCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
    // if game exists
	if (m_server->gameList.count(args.at(1)) > 0) {
		std::vector<std::string> msgVec;
		msgVec.push_back("exists");
		m_server->sendSerialized(senderSocket, msgVec);
		return;
	}
	//TODO: put mutex on gamelist
	//update gamelist with created game and player1 socket
	m_server->gameList[args.at(1)] = new GameSession(senderSocket);
	//TODO: release mutex on gamelist
}