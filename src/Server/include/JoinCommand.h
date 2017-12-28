//
// Created by chorin on 12/24/17.
//

#pragma once
#include <iostream>
#include "Command.h"
#include "Server.h"

class JoinCommand : public Command {
public:
    JoinCommand(Server &server) : Command(server) {}
    virtual void execute(std::vector<std::string> &args, int senderSocket = 0, int otherSocket = 0);
};