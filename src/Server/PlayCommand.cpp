//
// Created by chorin on 12/22/17.
//

#include "PlayCommand.h"

void PlayCommand::execute(std::vector<std::string> &args, int senderSocket, int otherSocket) {
	if (senderSocket == 0 || otherSocket == 0)
		throw "From PlayCommand::execute - can't play, one of the sockets is empty";
	// if player has no moves
	if (args.at(1)=="noMove")
		return;
	try {
		m_server->sendSerialized(otherSocket, args);
	} catch (const char *msg){
		throw;
	}
}