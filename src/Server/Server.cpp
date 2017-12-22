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

using std::string;
using std::cout;
using std::endl;

#define MAX_CONNECTED_CLIENTS 2
#define MAX_BUFFER_SIZE 512

// must set static members globally
const Server::Pos Server::noMovePos = Pos(-5,-5);
const Server::Pos Server::endGamePos = Pos(-1,-1);

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

		cout << "Waiting for client connections..." << endl;
		int socketP1 = 0;
		int socketP2 = 0;

		try {
			socketP1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
			cout << "Client1 connected" << endl;
			if (socketP1 == -1)
				throw "Error on accepting client1";

			socketP2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
			cout << "Client2 connected" << endl;
			if (socketP2 == -1)
				throw "Error on accepting client2";

			// send each player his player number by connection order
			int send = 1;
			int n = write(socketP1, &send, sizeof(int));
			if (n==-1)
				throw "Error sending player number";
			if (n==0)
				throw "Client1 disconnected";

			send = 2;
			n = write(socketP2, &send, sizeof(int));
			if (n==-1)
				throw "Error sending player number";
			if (n==0)
				throw "Client2 disconnected";

		} catch (const char* msg) {
			cout << "couldn't set up connection. Reason: " << msg << endl;
			continue;
		}

		try {
			//begin the game (start sending moves from one client to the other)
			handleClients(socketP1, socketP2);
		} catch (const char* msg) {
			cout << "error handling clients. reason: " << msg << endl;
		}

		//close communication
        cout << "Closing Sockets to both players.." << endl;
		close(socketP1);
		close(socketP2);
	}
}

void Server::handleClients(int socketP1,int socketP2) {

	int* currSocket = &socketP1;
	int* otherSocket = &socketP2;
	Pos pos(0,0);

	do {
		int n = read(*currSocket, &pos, sizeof(pos));
		if (n==-1)
			throw "Error reading pos";
		if (n==0)
			throw "Client disconnected";

		if (pos != noMovePos && pos != endGamePos) {
			// player is able to play, send move to other player
			n = write(*otherSocket, &pos, sizeof(pos));
			if (n==-1 || n==0)
				throw "Error sending pos";
		}

        // switch players
        currSocket = (currSocket == &socketP1)? &socketP2 : &socketP1;
        otherSocket = (otherSocket == &socketP1)? &socketP2 : &socketP1;
	} while (pos != endGamePos);
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