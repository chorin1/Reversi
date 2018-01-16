/**
*  Reversi - Advanced Programming 1
*  Ex: #7
*  Join an open game session
*  updates the gamelist and tells the server to handle the session.
*  Returns a message to the client if game doesn't exist.
*/

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"

class JoinCommand : public Command {
public:
	JoinCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0);
};