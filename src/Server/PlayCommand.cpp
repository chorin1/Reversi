//
// Created by chorin on 12/22/17.
//

#include "PlayCommand.h"

void PlayCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	if (senderSocket == 0 || otherSocket == 0)
		throw "didn't get sockets in PlayCommand::execute";
	// if player has no moves
	if (args.at(1)=="noMove")
		return;
	try {
		m_server->sendSerialized(otherSocket, args);
	} catch (const char *msg){
		throw;
	}
}