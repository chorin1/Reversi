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
#include <csignal>
#include "../include/Server.h"
#include "../include/GameList.h"
#include "../include/Logging.h"

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
	pthread_mutex_init(&threadListMutex, NULL);
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
	pthread_mutex_init(&threadListMutex, NULL);
}

Server::~Server() {
	delete commManager;
}

void* Server::startThreadedStatic (void *tArgs) {
	Server* serverP = (Server*) tArgs;
	int &listeningSocket = serverP->serverSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	while (listeningSocket != -1) {
			int tempSocket = 0;
			tempSocket = accept(listeningSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
			if (tempSocket == -1)
				cout << "Error on client accept" << endl;
			else {
				cout << "client connected!" << endl;
				// create new struct with client socket & server pointer for thread
				HandleClientThreadArgs *newClientArgs = (HandleClientThreadArgs *) malloc(sizeof(HandleClientThreadArgs));
				newClientArgs->serverP = serverP;
				newClientArgs->socket = tempSocket;
				//handle client with a new thread
				pthread_t new_thread;
				int rc = pthread_create(&new_thread, NULL, Server::HandleClientStatic, newClientArgs);
				if (rc) {
					cout << "Error: unable to create thread, " << rc << endl;
					exit(-1);
				}
				// add new thread to thread list

				LOG("After accept! locking thread mutex");
				pthread_mutex_lock(&serverP->threadListMutex);
				serverP->threadsList.push_back(new_thread);
				pthread_mutex_unlock(&serverP->threadListMutex);
				LOG("After accept! mutex released");
			}
	}
}

void Server::start() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		throw "Error opening socket";
	struct sockaddr_in serverAddress;
	bzero((void *) &serverAddress, sizeof(serverAddress));
	int yes=1;
	// make bind errors go away for socket re-use
	if (setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
		throw "Error binding";
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	//ignore SIGPIPE errors
	signal(SIGPIPE, SIG_IGN);
	cout << "ready to accept new connections.." << endl;

	// start a new thread for main listening socket
	pthread_t mainThread;
	int nc = pthread_create(&mainThread, NULL, Server::startThreadedStatic, this);
	if (nc) {
		cout << "Error: unable to create main thread, " << mainThread << endl;
		exit(-1);
	}
	// add main listening thread to thread list
	pthread_mutex_lock(&threadListMutex);
	threadsList.push_back(mainThread);
	pthread_mutex_unlock(&threadListMutex);
}

void Server::HandleSession(int socketP1, int socketP2) {
	int* currSocket = &socketP1;
	int* otherSocket = &socketP2;
	bool closedSession = false;
	do {
		try {
			std::vector<std::string> netMessage = receiveSerialized(*currSocket);
			commManager->executeCommand(netMessage.front(), netMessage, *currSocket, *otherSocket);
		} catch (const char *msg) {
			// if one of the clients disconnected/errored the game will end.
			LOG(msg);
			closedSession = true;
		}
		currSocket = (currSocket == &socketP1)? &socketP2 : &socketP1;
		otherSocket = (otherSocket == &socketP1)? &socketP2 : &socketP1;
	} while (!closedSession);
	close(socketP1);
	close(socketP2);
}

std::vector<std::string> Server::receiveSerialized(int &fromSocket) {
	int stringSize = 0;
	char msgBuffer[MAX_BUFFER_SIZE] = "";
	std::vector<std::string> vec;

	// get string size
	int n = read(fromSocket, &stringSize, sizeof(stringSize));
	if (n == -1)
		throw "Error reading string size";
	if (n == 0)
		throw "client disconnected..";

	LOG("expecting size of: " << stringSize << " bytes");
	n = read(fromSocket, &msgBuffer, stringSize);
	if (n == -1)
		throw "Error getting serialized msg";
	if (n == 0)
		throw "client disconnected..";

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
	LOG("sending message: " << msgBuffer);
	LOG("size is: " << msgSize);
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
	LOG("inside deleteCurrThread()");
	pthread_mutex_lock(&threadListMutex);
	LOG("inside deleteCurrThread() - mutex locked");
	for (std::vector<pthread_t>::iterator it = threadsList.begin(); it!=threadsList.end(); ++it) {
		if (pthread_equal(pthread_self(), *it)) {
			cout << "removing thread #" << pthread_self() << endl;
			threadsList.erase(it);
			break;
		}
	}
	pthread_mutex_unlock(&threadListMutex);
	LOG("inside deleteCurrThread() - mutex unlocked");
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
	cout << "handling socket #" << args->socket << endl;

	// get and exec command from new connected client
	std::vector<std::string> netMessage = receiveSerialized(args->socket);
	commManager->executeCommand(netMessage.front(), netMessage, args->socket);

	LOG("finished execute command, deleting thread");
	deleteCurrThread();
	free(args);
	LOG("thread is ending");
}

void Server::stop() {
	cout << "closing listener socket" << endl;
	close(serverSocket);
	// change server socket so main thread will know to end
	serverSocket = -1;
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
		pthread_cancel(*it);
	}
	pthread_mutex_unlock(&threadListMutex);
	cout << "all threads closed" << endl;
}