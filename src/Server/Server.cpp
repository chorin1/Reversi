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
#include <pthread.h>
#include "Server.h"
#include "GameList.h"

using std::string;
using std::cout;
using std::endl;

struct HandleClientThreadArgs {
	int socket;
	Server* serverP;
};

Server::Server(int port) : port(port), serverSocket(0) {
	cout << "Setting up server on custom port " << port << endl;
	commManager = new CommandsManager(*this);
}

Server::Server() {
	std::ifstream configFile;
	configFile.open("serverConfig.txt");
	if (!configFile.is_open())
		cout << "Error opening serverConfig.txt" << endl;

	string inputStr;
	configFile >> inputStr;
	configFile.close();

	port = atoi(inputStr.c_str());
	if (port < 1 || port > 65535)
		cout << "Error parsing port from config file" << endl;

	cout << "Setting up server on port " << port << endl;
	serverSocket = 0;
	commManager = new CommandsManager(*this);
}

Server::~Server() {
	delete commManager;
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
		int tempSocket = 0;
		tempSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
		if (tempSocket == -1)
			cout << "Error on client accept" << endl;
		else {
			cout << "Client connected!" << endl;
			// create new struct with client socket for thread
			HandleClientThreadArgs *newClientArgs = (HandleClientThreadArgs *) malloc(sizeof(HandleClientThreadArgs));
			newClientArgs->serverP = this;
			newClientArgs->socket = tempSocket;
			//handle client with a new thread
			pthread_t new_thread;
			int rc = pthread_create(&new_thread, NULL, Server::HandleClientStatic, newClientArgs);
			if (rc) {
				cout << "Error: unable to create thread, " << rc << endl;
				exit(-1);
			}
			// add new thread to thread list
			pthread_mutex_lock(&threadListMutex);
			threadsList.push_back(new_thread);
			pthread_mutex_unlock(&threadListMutex);
		}
	}
	/* OLD ONE THREADED CODE
	while (true) {
		int clientSocket = 0;
		cout << "Waiting for client connections..." << endl;
		try {
			clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
			cout << "Client #" << clientSocket << " connected" << endl;
			if (clientSocket == -1)
				throw "Error on accepting client";
			std::vector<std::string> netMessage = receiveSerialized(clientSocket);
			commManager->executeCommand(netMessage.front(), netMessage, clientSocket);
		} catch (const char* msg) {
			cout << "Error with client #" << clientSocket << " Reason: " << msg << endl;
			continue;
		}
	}
	 */
}

void Server::HandleSession(int socketP1, int socketP2) {
	int* currSocket = &socketP1;
	int* otherSocket = &socketP2;
	bool closedGame = false;
	do {
		try {
			std::vector<std::string> netMessage = receiveSerialized(*currSocket);
			commManager->executeCommand(netMessage.front(), netMessage, *currSocket, *otherSocket);
			// to check if clients disconnected
			if (netMessage.front()=="close")
				closedGame = true;
		} catch (const char *msg) {
			cout << msg << endl;
			closedGame = true;
		}
		currSocket = (currSocket == &socketP1)? &socketP2 : &socketP1;
		otherSocket = (otherSocket == &socketP1)? &socketP2 : &socketP1;
	} while (!closedGame);
}

void Server::stop() {
	// close listener socket
	cout << "closing listener socket" << endl;
	close(serverSocket);
	// close all handle sockets
	pthread_mutex_lock(&GameList::getInstance().gameListMutex);
	std::map <std::string, GameSession*> &sessionMap = GameList::getInstance().getInstance().gameSessionMap;
	for (std::map <std::string, GameSession*>::iterator it = sessionMap.begin(); it!=sessionMap.end(); ++it) {
		cout << "closing socket #" << it->second->player1Socket << endl;
		close(it->second->player1Socket);
		cout << "closing socket #" << it->second->player2Socket << endl;
		close(it->second->player2Socket);
	}
	pthread_mutex_unlock(&GameList::getInstance().gameListMutex);

	cout << "closing threads" << endl;
	pthread_mutex_lock(&threadListMutex);
	for (std::vector<pthread_t>::iterator it = threadsList.begin(); it!=threadsList.end(); ++it) {
		pthread_join(*it, NULL);
	}
	pthread_mutex_unlock(&threadListMutex);
	cout << "all threads closed" << endl;
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

void Server::deleteCurrThread() {
	pthread_mutex_lock(&threadListMutex);
	for (std::vector<pthread_t>::iterator it = threadsList.begin(); it!=threadsList.end(); ++it) {
		if (pthread_equal(pthread_self(), *it)) {
			cout << "Removing thread #" << pthread_self() << endl;
			threadsList.erase(it);
		}
	}
	pthread_mutex_unlock(&threadListMutex);
}

void Server::closeSocket(int socketToClose) {
	close(socketToClose);
}

void* Server::HandleClientStatic(void* object) {
	struct HandleClientThreadArgs *args = (struct HandleClientThreadArgs *)object;
	args->serverP->handleClient(args);
}

void* Server::handleClient(void *tArgs) {
	struct HandleClientThreadArgs *args = (struct HandleClientThreadArgs *) tArgs;
		cout << "in handleClient, handling socket #" << args->socket << endl;

	// get and exec command from new connected client
	std::vector<std::string> netMessage = receiveSerialized(args->socket);
	commManager->executeCommand(netMessage.front(), netMessage, args->socket);

	deleteCurrThread();
	free(args);
}