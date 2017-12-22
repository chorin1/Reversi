/**
*  Reversi - Advanced Programming 1
*  Ex: #4
*  Human player through network.
*  the class uses the Client class to send and recieve moves to the server
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
	// sends the move played to the server
	virtual void sendMove(GameModel::Pos pos) const;
private:
	Client *const m_client;
};