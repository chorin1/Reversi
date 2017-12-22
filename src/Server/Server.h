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

class Server {
public:
    // simple struct to get positions, copied from the gameModel by Roi's recommendation
    struct Pos {
        int m_x;
        int m_y;
        Pos (int x,int y): m_x(x), m_y(y) {}
        Pos (const Pos& other): m_x(other.m_x), m_y(other.m_y) {}
        bool operator==(const Pos& pos2) const {
            return pos2.m_x == m_x && pos2.m_y == m_y;
        }
        bool operator!=(const Pos& pos2) const {
            return !(*this == pos2);
        }
    };

    // create a server with a custom port
    Server(int port);
    // create a server and get port from the serverConfig.txt file
    Server();

    // start the server, 2 clients will be handled until game ends or one of them disconnected.
    // the server will then allow 2 new clients to connect
    void start();

    // stop the server
    void stop();

    // constant used to define if the game has ended or if the current player has no available moves
    const static Pos noMovePos;
    const static Pos endGamePos;

    // send and receive serialized data from socket (each string is seperated by '~') and extract to vector
    std::vector<std::string> receiveSerialized(int &fromSocket);
    void sendSerialized(int &toSocket, std::vector<std::string> &vec);
private:
    int port;
    int serverSocket;
    void handleClients(int clientSocket,int clientSocket2);
};
