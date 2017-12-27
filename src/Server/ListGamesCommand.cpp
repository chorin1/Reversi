//
// Created by chorin on 12/23/17.
//

#include <string>
#include <vector>
#include <map>
#include "ListGamesCommand.h"
#include "GameList.h"
using std::string;
using std::vector;
using std::map;

void ListGamesCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
    vector<string> listMsg;
    std::map<std::string, GameSession*> &sessionMap = GameList::getInstance().gameSessionMap;
    // get game list & lock with mutex gamelist extraction so iterator wont get lost
    pthread_mutex_lock(&GameList::getInstance().gameListMutex);

    for(map<string,GameSession*>::iterator it = sessionMap.begin(); it != sessionMap.end(); ++it) {
        // if game is missing a player, add to the sendback message
        if (it->second->player2Socket==0)
            listMsg.push_back(it->first);
    }
    pthread_mutex_unlock(&GameList::getInstance().gameListMutex);

    // send list of open games
    try {
        m_server->sendSerialized(senderSocket, listMsg);
    } catch (const char* msg) {
        handleErr(msg);
    }

    m_server->closeSocket(senderSocket);
}