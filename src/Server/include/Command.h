/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  abstract command, used as interface and error handling of commands (by command design pattern)
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Server.h"

class Server;

class Command {
public:
	Command(Server &server): m_server(&server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0) = 0;
	virtual ~Command() {}
protected:
	Server* m_server;
	// error handler
	void handleErr(char const* msg) {
		std::cout << "thread #" << pthread_self() << " threw " << msg << std::endl;
	}
};