//Command Interface

#pragma once
#include <vector>
#include <string>
#include "Server.h"

class Server;

class Command {
public:
	Command(Server &server): m_server(&server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket = 0, int otherSocket = 0) = 0;
	virtual ~Command() {}
protected:
	Server* m_server;
};