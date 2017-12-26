//
// Created by chorin on 12/24/17.
//

#include <map>
#include <string>
#include <vector>
#include "JoinCommand.h"
#include "GameSession.h"

void JoinCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
    std::vector<std::string> msgVec;
    std::map<std::string, GameSession*>::iterator it = m_server->gameList.find(args.at(1));
    // if game doesnt exist
    if (it == m_server->gameList.end()) {
        msgVec.push_back("not exist");
        m_server->sendSerialized(senderSocket, msgVec);
        return;
    }
    //TODO: put mutex on gamelist
    it->second->player2Socket = senderSocket;
    // a temp object is created to release mutex quickly (without waiting messages to be sent to clients)
    GameSession tempGS;
    tempGS.player1Socket = it->second->player1Socket;
    tempGS.player2Socket = it->second->player2Socket;
    //TODO: release mutex

    //send each client its role
    msgVec.push_back("player1");
    m_server->sendSerialized(tempGS.player1Socket, msgVec);

    msgVec.clear();
    msgVec.push_back("player2");
    m_server->sendSerialized(tempGS.player2Socket, msgVec);

    //TODO: create new thread
    //m_server->handleClients(tempGS.player1Socket, tempGS.player2Socket);
}