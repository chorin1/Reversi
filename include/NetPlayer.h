/**
*  Reversi - Advanced Programming 1
*  Ex: #4
*  Human player through network.
*  the class depends on the Client class to send and recieve moves from a player
*  across the network
*/

#pragma once
#include "GameModel.h"
#include "Player.h"
#include "Client.h"

class NetPlayer : public Player {

public:
    NetPlayer (Client& client) : m_client(&client) {}
    ~NetPlayer() {}
    GameModel::Pos makeMove(const GameModel* const = NULL) const;
    virtual void sendMove(GameModel::Pos pos) const;
private:
    Client *const m_client;
};

