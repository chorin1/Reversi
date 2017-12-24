//
// Created by chorin on 12/23/17.
//

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"


class CloseCommand : public Command {
public:
	CloseCommand(Server &server) : Command(server) {}
	virtual void execute(std::vector<std::string> &args, int senderSocket = 0, int otherSocket = 0);
};