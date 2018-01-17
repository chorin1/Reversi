/**
*  Reversi - Advanced Programming 1
*  Ex: #7
*  multi-threaded server class used to handle connections.
*  handling each client request is done by sending each command (using the Command pattern) to the threadPool.
*  Main server listener thread and long-term sessions thread will be handled by the server.
*/

#pragma once
#include <vector>
#include <string>
#include <map>
#include "GameSession.h"
#include "CommandsManager.h"
#include "ThreadPool.h"

#define MAX_CONNECTED_CLIENTS 10
#define MAX_BUFFER_SIZE 512
#define THREADS_IN_POOL 5

class CommandsManager;

class Server {
public:
	// create a server with a custom port
	Server(int port);
	// create a server and get port from the serverConfig.txt file
	Server();
	~Server();

	// start listening for new connections and handling requests
	void start();

	// close all open sockets and running threads
	void stop();

	/* send and receive serialized data from socket (each string is separated by '~')
	 * buffer size is exactly the vector size (for network efficiency) - an int of the msg size will be sent beforehand
	 * throws const char* errors.
	 * first element of vector is the command.
	 */
	std::vector<std::string> receiveSerialized(int &fromSocket);
	void sendSerialized(int &toSocket, std::vector<std::string> &vec);

	// handle a long-term session between 2 clients
	void handleSession(int clientSocket, int clientSocket2);

	// stop and delete current thread from the longTermThreadList
	void deleteCurrThreadFromList();

	/*
	 * start a new (long-term) session between 2 clients.
	 * a new thread will be created and saved on the long-term thread list.
	 * the current thread will end to free up the threadPool queue.
	 */
	void newSession(int socket1, int socket2);

	// close the socket
	void closeSocket(int socketToClose);
private:
	int port;
	int serverSocket;
	CommandsManager* commManager;
	ThreadPool* threadPool;

	pthread_mutex_t threadListMutex;
	// stores long-term sessions and main listener thread (so they wont lock the threadPool)
	std::vector<pthread_t> longTermThreadList;

	void *handleClient(void *tArgs);

	// static handle function to handle a pthread for the main server socket
	static void *startThreadedStatic(void *tArgs);
	// static handle function to handle client request with pthreads
	static void *handleClientStatic(void *object);
	// static handle function to handle an new session with pthread
	static void *handleSessionStatic(void *sessionArgs);
};