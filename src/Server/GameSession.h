//
// Created by chorin on 12/23/17.
//

#pragma once
class GameSession {
public:
    GameSession(int p1Socket) : player1Socket(p1Socket), player2Socket(0) {}
    GameSession(int p1Socket, int p2Socket) : player1Socket(p1Socket), player2Socket(p2Socket) {}
    int player1Socket;
    int player2Socket;
};