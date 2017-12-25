//
// Created by chorin on 12/22/17.
//

#include "CommandsManager.h"
#include "PlayCommand.h"
#include "CloseCommand.h"
#include "ListGamesCommand.h"
#include "StartCommand.h"
#include "Server.h"

CommandsManager::CommandsManager(Server &server) {
	commandsMap["play"] = new PlayCommand(server);
	commandsMap["close"] = new CloseCommand(server);
	commandsMap["list_games"] = new ListGamesCommand(server);
    commandsMap["start"] = new StartCommand(server);
}

void CommandsManager::executeCommand(std::string &command, std::vector<std::string> &args,
									 int senderSocket, int otherSocket) {
	if (commandsMap.count(command)==0) {
		std::cout << "Trying to execute unknown command: " << command << std::endl;
		return;
	}
	Command *commandObj = commandsMap[command];
	try {
		commandObj->execute(args, senderSocket, otherSocket);
	} catch (const char *msg) {
		throw;
	}
}

CommandsManager::~CommandsManager() {
	std::map<std::string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}