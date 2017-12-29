/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  return a list to the sender with the open sessions.
*  closes socket.
*/

#pragma once
#include "Command.h"
#include "Server.h"

class ListGamesCommand : public Command {
	public:
	ListGamesCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0);
};