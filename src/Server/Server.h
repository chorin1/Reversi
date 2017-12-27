/**
*  Reversi - Advanced Programming 1
*  Ex: #4
*  Date: 27/11/17
*  Server class used to handle 2 Reversi clients in a networked game
*  class uses linux sockets only
*  will send positions from one player to the other until the game has ended.
*  Each Client runs its own copy of the game
*/

#pragma once
#include <vector>
#include <string>
#include <map>
#include "GameSession.h"
#include "CommandsManager.h"

#define MAX_CONNECTED_CLIENTS 2
#define MAX_BUFFER_SIZE 512

class CommandsManager;

class Server {
public:
    // create a server with a custom port
    Server(int port);
    // create a server and get port from the serverConfig.txt file
    Server();
    // start the server, 2 clients will be handled until game ends or one of them disconnected.
    // the server will then allow 2 new clients to connect
    ~Server();
    void start();

    // stop the server
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

    pthread_mutex_t threadListMutex;
    std::vector<pthread_t> threadsList;

    // static handle function to use with pthreads
    static void *HandleClientStatic(void *object);
    // function that each thread runs
    void *handleClient(void *tArgs);
};