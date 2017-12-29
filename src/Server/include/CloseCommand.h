/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  Close command, used to close an open session between 2 players.
*  deletes the game from the game list and closes the players sockets.
*/

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"

class CloseCommand : public Command {
public:
	CloseCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket, int otherSocket = 0);
};