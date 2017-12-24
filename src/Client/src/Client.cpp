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

#define MAX_BUFFER_SIZE 512

using std::cout;
using std::endl;
using std::string;

//TODO: no need to send endgame (will be sent outside) when client destructs
//must set static members globally
//const GameModel::Pos Client::noMovePos = GameModel::Pos(-5,-5);
//const GameModel::Pos Client::endGamePos = GameModel::Pos(-1,-1);

Client::Client() {
	const char* serverIP;
	int port;

	std::ifstream configFile;
	configFile.open("config.txt");
	if (!configFile.is_open())
		throw("error opening config.txt");
	string inputStr;
	configFile >> inputStr;
	configFile.close();

	if (inputStr.find(':') == std::string::npos)
		throw("error parsing config file");

	string serverIPstring = inputStr.substr(0, inputStr.find(':'));
	serverIP = serverIPstring.c_str();

	string serverPortString = inputStr.substr(inputStr.find(':') + 1);
	port = atoi(serverPortString.c_str());

	if (port < 1 || port > 65535)
		throw("error parsing port from config file");

	std::cout << "Trying to connect to " << serverIP << ":" << port << endl;

	this->serverIP = serverIP;
	this->serverPort = port;
	clientSocket = 0;
}

Client::Client(const char *serverIP, int serverPort):
		serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}

void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		throw "Error opening socket";

	//convert IP to network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address))
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
	int clientsPlayerNum = 0;
	int n = read(clientSocket, &clientsPlayerNum, sizeof(clientsPlayerNum));
	if (n == -1)
		throw "Error reading player num from socket";
	return clientsPlayerNum;
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

void Client::disconnect() {
	// send close message to server
	std::vector<std::string> closeMsg;
	closeMsg.push_back("close");
	closeMsg.push_back("sessionName");
	sendSerialized(closeMsg);
	close(clientSocket);
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
		throw "client disconnected..";

	//TODO: remove cout
	cout << "expecting size of: " << stringSize << " bytes" << endl;
	n = read(clientSocket, &msgBuffer, stringSize);
	if (n == -1)
		throw "Error getting serialized msg";
	if (n == 0)
		throw "client disconnected..";

	//TODO: remove cout
	cout << "Got full buffer: " << msgBuffer << endl;

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
		assert(strlen(msgBuffer) + i->length() + 2 < MAX_BUFFER_SIZE);
		strcat(msgBuffer, i->c_str());
		strcat(msgBuffer, "~");
	}
	// now msgBuffer is filled with messages separated by '~' with '\0' at end
	int msgSize = sizeof(char) * (strlen(msgBuffer) + 1);
	//TODO: remove couts
	cout << "sending message: " << msgBuffer << endl;
	cout << "size is: " << msgSize << endl;
	int n = write(clientSocket, &msgSize, sizeof(int));
	if (n == -1)
		throw "Error writing length to socket";
	if (n == 0)
		throw "client disconnected..";

	n = write(clientSocket, &msgBuffer, msgSize);
	if (n == -1)
		throw "Error writing buffer to socket";
	if (n == 0)
		throw "client disconnected..";
}

int Client::numberOfGames(){
	int numberOfGames = 0;
	int n = read(clientSocket, &numberOfGames, sizeof(numberOfGames));
	if (n == -1)
		throw "Error reading number of games from socket";
	return numberOfGames;
}

void Client::numberOption(int option){
	int n = write(clientSocket, &option, sizeof(option));
	if (n == -1)
		throw "Error writing number of game from socket";
	if (n == 0)
		throw "client disconnect..";

}