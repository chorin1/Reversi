//
// Created by chorin on 12/3/17.
//

#pragma once
#include "GameModel.h"

class Client {
public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    int sendMove(GameModel::Pos pos);
    GameModel::Pos getMove();
    void disconnect();
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};

