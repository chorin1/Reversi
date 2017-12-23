//
// Created by chorin on 12/23/17.
//

#pragma once
class GameSession {
public:
    GameSession(int player1Socket) : player1Socket(player1Socket) {}
    int player1Socket;
    int player2Socket = 0;
};