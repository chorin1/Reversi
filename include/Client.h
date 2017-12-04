//
// Created by chorin on 12/3/17.
//

#pragma once
#include "GameModel.h"

class Client {
public:
    //TODO: get server address from file
    Client(const char *serverIP, int serverPort);
    // connect to the designated server
    void connectToServer();
    // get client's player number
    int getClientPlayerNum();
    void sendMove(GameModel::Pos pos);
    GameModel::Pos getMove();
    void disconnect();

    //these values will be sent to server when the local player can't move or to notify server that game has ended
    static const GameModel::Pos noMovePos;
    static const GameModel::Pos endGamePos;
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};
