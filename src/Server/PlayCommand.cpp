//
// Created by chorin on 12/22/17.
//

#include "PlayCommand.h"

void PlayCommand::execute(std::vector<std::string> args, int senderSocket, int otherSocket) {
	if (senderSocket == 0 || otherSocket == 0)
		throw "didn't get sockets in PlayCommand::execute";
	try {
		m_server->sendSerialized(otherSocket, args);
	} catch (const char *msg){
		throw;
	}
}