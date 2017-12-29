/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  used in an ongoing session, the command will send the player move to the other socket.
*  socket remains open.
*/

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"


class PlayCommand : public Command {
public:
	PlayCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0);
};
