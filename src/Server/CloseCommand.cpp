//
// Created by chorin on 12/23/17.
//

#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include "GameList.h"
#include "CloseCommand.h"

void CloseCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	//close socket
	close(senderSocket);
	close(otherSocket);

    pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	// delete game from gamelist
	std::map<std::string, GameSession*> &sessionMap = GameList::getInstance().gameSessionMap;
	std::map<std::string, GameSession*>::iterator it = sessionMap.find(args.at(1));
	if (it != sessionMap.end()) {
		delete (it->second);
		sessionMap.erase(it);
	}
    pthread_mutex_unlock(&GameList::getInstance().gameListMutex);
}