/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  Client class, respoinsble for all communication with the server (listing games, creating, joining,
*  playing etc.
*  each message (string vector) is serialized and sent: first by sending the message size and then the content.
*/

#pragma once
#include "GameModel.h"
#include <string>

// pos that will be sent to server if no move is possible
#define NO_MOVE_POS GameModel::Pos(-5,-5)

class Client {
public:
	// create a client with server IP & port from the config.txt file
	Client();
	// create a client with a custom server IP & port
	Client(const char *serverIP, int serverPort);
	~Client();

	// connect to the designated server
	void connectToServer();

	// send a move to the server
	void sendMove(GameModel::Pos pos);
	// get a move from the server
	GameModel::Pos getMove();
	// disconnect from server
	void disconnect();

	// methods for getting game list from server, joining a game and creating a new game
	std::vector<std::string> getOpenSessions();
	int joinGame(std::string gameName);
	int createGame(std::string gameName);
	// send close command to server to end current game session
	void closeSession();

	// current session name (used for close command at end of session)
	const std::string &getSessionName() const;
	void setSessionName(const std::string &sessionName);

	const std::string &getServerIP() const;
	int getServerPort() const;

private:
	std::string serverIP;
	int serverPort;
	int clientSocket;
	std::string sessionName;
	// send and receive serialized data from socket (each string is separated by '~' on the buffer)
	std::vector<std::string> receiveSerialized();
	void sendSerialized(std::vector<std::string> &vec);
	// extract the client player num from message vector recieved from server
	int extractPlayerNumFromVec(std::vector<std::string> &msgVec);
};