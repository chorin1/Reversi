/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  creates a new game session.
*  updates the gamelist and tells the server to handle the session.
*  returns a message to the client if game doesn't exist.
*/


#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"


class StartCommand : public Command {
public:
	StartCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0);
};