/*
*  Client.cpp
*
*/

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include "../include/Client.h"
#include <string>
#include "../include/Logging.h"

#define MAX_BUFFER_SIZE 512

using std::cout;
using std::endl;
using std::string;

Client::Client() {

	std::ifstream configFile;
	configFile.open("config.txt");
	if (!configFile.is_open())
		throw("error opening config.txt");
	string inputStr;
	configFile >> inputStr;
	configFile.close();

	if (inputStr.find(':') == std::string::npos)
		throw("error parsing config file");

	serverIP = inputStr.substr(0, inputStr.find(':'));


	string serverPortString = inputStr.substr(inputStr.find(':') + 1);
	int port = atoi(serverPortString.c_str());

	if (port < 1 || port > 65535)
		throw("error parsing port from config file");

	this->serverPort = port;
	clientSocket = 0;
}

Client::Client(const char *serverIP, int serverPort):
		serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}

void Client::connectToServer() {
	const char* IPcharp = serverIP.c_str();
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		throw "Error opening socket";

	//convert IP to network address
	struct in_addr address;
	if (!inet_aton(IPcharp, &address))
		throw "Can't parse IP address";
	struct hostent *server;
	server = gethostbyaddr((const void* )&address, sizeof(address), AF_INET);
	if (server==NULL)
		throw "Host is unreachable";

	struct sockaddr_in serverAddress;
	bzero((char*)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		throw "Error connecting to server";
}

int Client::getClientPlayerNum() {
	std::vector<std::string> msgVec;
	try {
		std::vector<std::string> msgVec = receiveSerialized();
	} catch (const char* msg) {
		throw;
	}
	if (msgVec.front() == "player1")
		return 1;
	if (msgVec.front() == "player2")
		return 2;
	else
		throw "Error: got other message while expecting player number from server";
}

GameModel::Pos Client::getMove() {
	GameModel::Pos pos(0, 0);
	std::vector<std::string> messageVec;

	try {
        messageVec = receiveSerialized();
	} catch (const char* msg) {
		throw;
	}
	// message from server
	if (messageVec.front()=="msg") {
		cout << messageVec.at(1) << endl;
		return getMove();
	}
	//valid move
	if (messageVec.front()=="play") {
		pos.m_x = atoi(messageVec.at(1).c_str());
		pos.m_y = atoi(messageVec.at(2).c_str());
		return pos;
	}
	throw "didn't get a compatible message from Server";
}

void Client::sendMove(GameModel::Pos pos) {
	std::vector<std::string> messageVec;
	// set up a vector of "play", "X", "Y"
    messageVec.push_back("play");
	if (pos == NO_MOVE_POS)
		messageVec.push_back("noMove");
	else {
		// convert number to string
		string coord = static_cast<std::ostringstream *>( &(std::ostringstream() << pos.m_x))->str();
		messageVec.push_back(coord);
		coord = static_cast<std::ostringstream *>( &(std::ostringstream() << pos.m_y))->str();
		messageVec.push_back(coord);
	}
	try {
		sendSerialized(messageVec);
	} catch (const char* msg) {
		throw;
	}
}

void Client::closeSession() {
	// send close message to server
	std::vector<std::string> msgVec;
	msgVec.push_back("close");
	msgVec.push_back(sessionName);
	sendSerialized(msgVec);
	disconnect();
}

std::vector<std::string> Client::receiveSerialized() {
	int stringSize = 0;
	char msgBuffer[MAX_BUFFER_SIZE] = "";
	std::vector<std::string> vec;

	// get string size
	int n = read(clientSocket, &stringSize, sizeof(stringSize));
	if (n ==- 1)
		throw "Error reading string size";
	if (n == 0)
		throw "server disconnected..";

	LOG("expecting size of: " << stringSize << " bytes");
	n = read(clientSocket, &msgBuffer, stringSize);
	if (n == -1)
		throw "Error getting serialized msg";
	if (n == 0)
		throw "server disconnected..";

	LOG("Got full buffer: " << msgBuffer);
	// convert c_string buffer with separating '~' to vector of std::string, '\0' is neglected
	int i=0;
	while (i < stringSize-1) {
		std::string strToAdd;
		while (msgBuffer[i] != '~' && i < stringSize-1) {
			strToAdd += msgBuffer[i];
			i++;
		}
		vec.push_back(strToAdd);
		i++;
	}
	return vec;
}

void Client::sendSerialized(std::vector<std::string> &vec) {
	char msgBuffer[MAX_BUFFER_SIZE] = "";
	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
		// check that a buffer overflow will not occur
		if (strlen(msgBuffer) + i->length() + 2 > MAX_BUFFER_SIZE)
            throw "trying to send too long message will cause buffer overflow";
		strcat(msgBuffer, i->c_str());
		strcat(msgBuffer, "~");
	}
	// now msgBuffer is filled with messages separated by '~' with '\0' at end
	int msgSize = sizeof(char) * (strlen(msgBuffer) + 1);

	LOG("sending message: " << msgBuffer);
	LOG("size is: " << msgSize << endl);
	int n = write(clientSocket, &msgSize, sizeof(int));
	if (n == -1)
		throw "error writing length to socket";
	if (n == 0)
		throw "server disconnected..";

	n = write(clientSocket, &msgBuffer, msgSize);
	if (n == -1)
		throw "error writing buffer to socket";
	if (n == 0)
		throw "server disconnected..";
}

Client::~Client() {
	disconnect();
}

void Client::disconnect() {
	close(clientSocket);
}

std::vector<std::string> Client::getOpenSessions() {
	std::vector<std::string> msgVec;
	msgVec.push_back("list_games");
	try {
		sendSerialized(msgVec);
		msgVec = receiveSerialized();
	} catch (const char* msg) {
		throw;
	}
	return msgVec;
}

int Client::joinGame(std::string gameName) {
	if (gameName.find('~')!=string::npos || gameName.find(' ')!=string::npos ||
			gameName.empty() || gameName.find("empty")!=string::npos)
		throw "Illegal game name entered.";
	std::vector<std::string> msgVec;
	msgVec.push_back("join");
	msgVec.push_back(gameName);
	try {
		sendSerialized(msgVec);
		msgVec = receiveSerialized();
	} catch (const char* msg) {
		throw;
	}
	if (msgVec.at(0) == "notexist")
		throw "There are no open games with the name you've entered.";
	if (msgVec.at(0) == "player1")
		return 1;
	if (msgVec.at(0) == "player2")
		return 2;
	throw "Got errored message from server while trying to create game.";
}

int Client::createGame(std::string gameName) {
	if (gameName.find('~')!=string::npos || gameName.find(' ')!=string::npos ||
		gameName.empty() || gameName.find("empty")!=string::npos)
		throw "illegal game name entered";
	std::vector<std::string> msgVec;
	msgVec.push_back("start");
	msgVec.push_back(gameName);
	try {
		sendSerialized(msgVec);
		cout << "Game \"" << gameName << "\" created!" << endl;
		cout << "Waiting for another player to join.." << endl;
		msgVec = receiveSerialized();
	} catch (const char* msg) {
		throw;
	}
	if (msgVec.at(0) == "exists")
		throw "Game with this name already exists.";
	if (msgVec.at(0) == "player1")
		return 1;
	if (msgVec.at(0) == "player2")
		return 2;
	throw "Got bad message from server while trying to create game.";
}

const string &Client::getSessionName() const {
	return sessionName;
}

void Client::setSessionName(const string &sessionName) {
	Client::sessionName = sessionName;
}

const string &Client::getServerIP() const {
	return serverIP;
}

int Client::getServerPort() const {
	return serverPort;
}