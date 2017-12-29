/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  the command manager creates and stores all available commands, whenever a request is being made
*  the command manager will execute the correct command.
*/

#pragma once
#include <map>
#include "Server.h"
#include "Command.h"

class Server;
class Command;

class CommandsManager {
public:
	CommandsManager(Server &server);
	~CommandsManager();
	void executeCommand(std::string &command, std::vector<std::string> &args,
										 int senderSocket, int otherSocket=0);
private:
	std::map<std::string, Command *> commandsMap;
};