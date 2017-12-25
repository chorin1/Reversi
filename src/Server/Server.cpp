/*
*  Server.cpp
*
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cassert>
#include "Server.h"
#include "CommandsManager.h"

using std::string;
using std::cout;
using std::endl;

#define MAX_CONNECTED_CLIENTS 2
#define MAX_BUFFER_SIZE 512

Server::Server(int port) : port(port), serverSocket(0) {
	cout << "Setting up server on custom port " << port << endl;
}

Server::Server() {
	std::ifstream configFile;
	configFile.open("serverConfig.txt");
	if (!configFile.is_open())
		throw("Error opening serverConfig.txt");

	string inputStr;
	configFile >> inputStr;
	configFile.close();

	port = atoi(inputStr.c_str());
	if (port < 1 || port > 65535)
		throw("Error parsing port from config file");

	cout << "Setting up server on port " << port << endl;
	serverSocket = 0;
}

Server::~Server() {
	std::map<std::string, GameSession*>::iterator it;
	for (it = gameList.begin(); it != gameList.end(); it++) {
		delete it->second;
	}
}

void Server::start() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		throw "Error opening socket";
	struct sockaddr_in serverAddress;
	bzero((void *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
		throw "Error binding";

	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	//define client socket structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	while (true) {
		int clientSocket = 0;
		cout << "Waiting for client connections..." << endl;
		try {
			clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
			cout << "Client #" << clientSocket << " connected" << endl;
			if (clientSocket == -1)
				throw "Error on accepting client";
			CommandsManager commandmngr(*this);
			std::vector<std::string> netMessage = receiveSerialized(clientSocket);
			commandmngr.executeCommand(netMessage.front(), netMessage, clientSocket);
		} catch (const char* msg) {
			cout << "Error with client #" << clientSocket << " Reason: " << msg << endl;
			continue;
		}
	}
}

void Server::handleClients(int socketP1,int socketP2) {
	int* currSocket = &socketP1;
	int* otherSocket = &socketP2;
	bool closedGame = false;
	do {
		try {
			CommandsManager commandmngr(*this);
			std::vector<std::string> netMessage = receiveSerialized(*currSocket);
			commandmngr.executeCommand(netMessage.front(), netMessage, *currSocket, *otherSocket);
			// to check if clients disconnected
			if (netMessage.front()=="close")
				closedGame = true;
		} catch (const char *msg) {
			throw;
		}
        currSocket = (currSocket == &socketP1)? &socketP2 : &socketP1;
        otherSocket = (otherSocket == &socketP1)? &socketP2 : &socketP1;
	} while (!closedGame);

	//kill thread
}

void Server::stop() {
	close(serverSocket);
}

std::vector<std::string> Server::receiveSerialized(int &fromSocket) {
	int stringSize = 0;
	char msgBuffer[MAX_BUFFER_SIZE] = "";
	std::vector<std::string> vec;

	// get string size
	int n = read(fromSocket, &stringSize, sizeof(stringSize));
	if (n ==- 1)
		throw "Error reading string size";
	if (n == 0)
		throw "client disconnected..";

	//TODO: remove cout
	cout << "expecting size of: " << stringSize << " bytes" << endl;
	n = read(fromSocket, &msgBuffer, stringSize);
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

void Server::sendSerialized(int &toSocket, std::vector<std::string> &vec) {
	char msgBuffer[MAX_BUFFER_SIZE] = "";
	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
		// check that a buffer overflow will not occur
		assert(strlen(msgBuffer) + i->length() + 2 < MAX_BUFFER_SIZE);
		strcat(msgBuffer, i->c_str());
		strcat(msgBuffer,"~");
	}
	// now msgBuffer is filled with messages separated by '~' with '\0' at end
	int msgSize = sizeof(char)*(strlen(msgBuffer)+1);
	//TODO: remove couts
	cout << "sending message: " << msgBuffer << endl;
	cout << "size is: " << msgSize << endl;
	int n = write(toSocket, &msgSize, sizeof(int));
	if (n == -1)
		throw "Error writing length to socket";
	if (n == 0)
		throw "client disconnected..";

	n = write(toSocket, &msgBuffer, msgSize);
	if (n == -1)
		throw "Error writing buffer to socket";
	if (n == 0)
		throw "client disconnected..";
}
