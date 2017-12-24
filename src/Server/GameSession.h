//
// Created by chorin on 12/23/17.
//

#pragma once
class GameSession {
public:
    GameSession(int player1Socket) : player1Socket(player1Socket) {player2Socket=0;}
    GameSession(int player1Socket, int player2Socket) : player1Socket(player1Socket), player2Socket(player2Socket) {}
    GameSession(const GameSession &other) {
        player1Socket = other.player1Socket;
        player2Socket = other.player2Socket;
    }
    int player1Socket;
    int player2Socket;
};