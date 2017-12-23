//
// Created by chorin on 12/23/17.
//

#include <unistd.h>
#include <vector>
#include <string>
#include "CloseCommand.h"

void CloseCommand::execute(std::vector<std::string> args, int senderSocket, int otherSocket) {
	//close sockets
	close(senderSocket);
	// TODO: find game (args.at(1)) in game list and delete
	// put mutex on gamelist object
	// delete gamename
	// close thread?
}