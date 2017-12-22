//
// Created by chorin on 12/22/17.
//

#pragma once
#include <map>
#include "Server.h"
#include "Command.h"

class CommandsManager {
public:
	CommandsManager(Server& server);
	~CommandsManager();
    void CommandsManager::executeCommand(std::string &command, const std::vector<std::string> &args,
                                         int senderSocket=0, int otherSocket=0);
private:
	std::map<std::string, Command *> commandsMap;
};