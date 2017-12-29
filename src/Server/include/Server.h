/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  multi-threaded server class used to handle connections.
*  handling each client request is done by creating a new thread and sending the command to a command manager.
*/

#pragma once
#include <vector>
#include <string>
#include <map>
#include "GameSession.h"
#include "CommandsManager.h"

#define MAX_CONNECTED_CLIENTS 10
#define MAX_BUFFER_SIZE 512

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
	 * can throw const char* errors.
	 * first element of vector is the command.
	 */
	std::vector<std::string> receiveSerialized(int &fromSocket);
	void sendSerialized(int &toSocket, std::vector<std::string> &vec);

	// handle a session between 2 clients
	void HandleSession(int clientSocket, int clientSocket2);

	// stop and delete current thread from threadlist
	void deleteCurrThread();

	// close the socket
	void closeSocket(int socketToClose);
private:
	int port;
	int serverSocket;
	CommandsManager* commManager;

	// vector that stores the living threads
	pthread_mutex_t threadListMutex;
	std::vector<pthread_t> threadsList;

	// static handle function to use with pthreads
	static void *HandleClientStatic(void *object);
	// execute client command, when execution ended the thread will delete itself from the thread list
	void *handleClient(void *tArgs);

	// static handle function to open a thread for the main socket
	static void *startThreadedStatic(void *tArgs);
};