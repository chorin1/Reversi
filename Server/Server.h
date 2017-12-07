//
// Created by nitaihalle on 12/4/17.
//

#pragma once

class Server {
public:
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


    Server(int port);
    Server();

    void start();
    void stop();

    const static Pos noMovePos;
    const static Pos endGamePos;
private:
    int port;
    int serverSocket;
    void handleClients(int clientSocket,int clientSocket2);
};
