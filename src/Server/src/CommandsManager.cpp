/*
*  CommandManager.cpp
*
*/

#include "../include/CommandsManager.h"
#include "../include/PlayCommand.h"
#include "../include/CloseCommand.h"
#include "../include/ListGamesCommand.h"
#include "../include/StartCommand.h"
#include "../include/Server.h"
#include "../include/JoinCommand.h"

CommandsManager::CommandsManager(Server &server) {
	commandsMap["play"] = new PlayCommand(server);
	commandsMap["close"] = new CloseCommand(server);
	commandsMap["list_games"] = new ListGamesCommand(server);
	commandsMap["start"] = new StartCommand(server);
	commandsMap["join"] = new JoinCommand(server);
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