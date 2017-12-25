//
// Created by chorin on 12/23/17.
//

#pragma once
#include "Command.h"
#include "Server.h"

class ListGamesCommand : public Command {
    public:
    ListGamesCommand(Server &server) : Command(server) {}
    virtual void execute(std::vector<std::string> &args, int senderSocket = 0, int otherSocket = 0);
};