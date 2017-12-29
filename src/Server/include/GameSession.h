/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  Each game session is 2 sockets. when a client creates a new game the second socket is init with 0
*  until another player has joined.
*/

#pragma once
class GameSession {
public:
	GameSession(int p1Socket) : player1Socket(p1Socket), player2Socket(0) {}
	GameSession(int p1Socket, int p2Socket) : player1Socket(p1Socket), player2Socket(p2Socket) {}
	int player1Socket;
	int player2Socket;
};