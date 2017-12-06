//
// Created by nitaihalle on 12/4/17.
//

#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H


#include <stdlib.h>

class Server {
public:
    Server(int port);

    Server(int port, int serverSocket);

    Server();

    struct Pos {
        int m_x;
        int m_y;
        Pos (int x,int y): m_x(x), m_y(y) {}
        //copy constructor
        Pos (const Pos& other): m_x(other.m_x), m_y(other.m_y) {}

        bool operator==(const Pos& pos2) const {
            return pos2.m_x == m_x && pos2.m_y == m_y;
        }
        bool operator!=(const Pos& pos2) const {
            return !(*this == pos2);
        }
    };

    void start();
    void stop();

private:
    int port;
    int serverSocket;

    void handleClient(int clientSocket,int clientSocket2);
    void getPos(Pos pos) const;
    Pos sendPos() const;
};


#endif //REVERSI_SERVER_H
