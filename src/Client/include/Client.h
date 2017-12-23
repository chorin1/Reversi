/**
*  Reversi - Advanced Programming 1
*  Ex: #4
*  Client class, connects to server and sends & recieves POS objects
*  if player is unable to move or game has ended
*  a special POS will be sent, set by const static values
*/

#pragma once
#include "GameModel.h"
#define NO_MOVE_POS GameModel::Pos(-5,-5)

class Client {
public:
	// create a client with server IP & port from the config.txt file
	Client();
	// create a client with a custom server IP & port
	Client(const char *serverIP, int serverPort);
	~Client() {this->disconnect();}

	// connect to the designated server
	void connectToServer();
	// get client's player number
	int getClientPlayerNum();
	// send a move to the server
	void sendMove(GameModel::Pos pos);
	// get a move from the server
	GameModel::Pos getMove();
	// disconnect from server
	void disconnect();

	//TODO: no need to send endgame (will be sent outside) when client destructs
	//these values will be sent to server when the local player can't move or to notify server that game has ended
	//static const GameModel::Pos noMovePos;
	//static const GameModel::Pos endGamePos;
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
	std::string currGameName;

	// send and receive serialized data from socket (each string is separated by '~')
	std::vector<std::string> receiveSerialized();
	void sendSerialized(std::vector<std::string> &vec);
};