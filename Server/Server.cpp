//
// Created by nitaihalle on 12/4/17.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Server.h"

using std::string;
using std::cout;
using std::endl;

#define MAX_CONNECTED_CLIENTS 2

// must set static members globally
const Server::Pos Server::noMovePos = Pos(-5,-5);
const Server::Pos Server::endGamePos = Pos(-1,-1);

Server::Server(int port) : port(port), serverSocket(0) {
	cout << "Setting up server on custom port..." << endl;
}

Server::Server() {
	const char* serverIP;

	std::ifstream configFile;
	configFile.open("serverConfig.txt");
	if (!configFile.is_open())
		throw("error opening serverConfig.txt");
	string inputStr;
	configFile >> inputStr;
	port = atoi(inputStr.c_str());
	if (port < 1 || port > 65535)
		throw("error parsing port from config file");
	cout << "Setting up server on port " << port << endl;

	configFile.close();
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

	while (true) {
		Pos pos(0,0);
		int n = read(*currSocket, &pos, sizeof(pos));
		if (n==-1)
			throw "Error reading pos";
		if (n==0)
			throw "Client disconnected";
		// game has ended
		if (pos == endGamePos)
			break;

		// player is able to play, send move to other player
		if (pos != noMovePos) {
			n = write(*otherSocket, &pos, sizeof(pos));
			if (n==-1 || n==0)
				throw "Error sending pos";
		}

        // switch players
        currSocket = (currSocket == &socketP1)? &socketP2 : &socketP1;
        otherSocket = (otherSocket == &socketP1)? &socketP2 : &socketP1;
	}
}

void Server::stop() {
	close(serverSocket);
}
