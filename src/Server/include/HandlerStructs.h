/**
*  Reversi - Advanced Programming 1
*  Ex: #7
*  handler structs for pthreads (that must use static methods)
*/

#pragma once
#include "Server.h"

struct HandleClientThreadArgs {
	int socket;
	Server* serverP;
};
struct HandleSessionThreadArgs {
	int socket1;
	int socket2;
	Server* serverP;
};
