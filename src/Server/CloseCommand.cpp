//
// Created by chorin on 12/23/17.
//

#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include "CloseCommand.h"

void CloseCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	//close socket
	close(senderSocket);
	close(otherSocket);
	// TODO: put mutex on gamelist object
	// delete game from gamelist
	std::map<std::string, GameSession*>::iterator it = m_server->gameList.find(args.at(1));
	if (it != m_server->gameList.end()) {
		delete (it->second);
		m_server->gameList.erase(it);
	}
}