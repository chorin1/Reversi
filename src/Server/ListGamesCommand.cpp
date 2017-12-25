//
// Created by chorin on 12/23/17.
//

#include <string>
#include <vector>
#include <map>
#include "ListGamesCommand.h"
#include "GameSession.h"
using std::string;
using std::vector;
using std::map;

void ListGamesCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
    vector<string> listMsg;
    for(map<string,GameSession*>::iterator it = m_server->gameList.begin(); it != m_server->gameList.end(); ++it) {
        // if game is missing a player, add to the sendback message
        if (it->second->player2Socket==0)
            listMsg.push_back(it->first);
    }
    try {
        m_server->sendSerialized(senderSocket, listMsg);
    } catch (const char *msg){
        throw;
    }
}