//
// Created by chorin on 12/22/17.
//

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"


class PlayCommand : public Command {
public:
	PlayCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket = 0, int otherSocket = 0);
};
