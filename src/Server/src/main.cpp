/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #5
 *  Server main
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include "../include/Server.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;

int main() {
	cout << "Welcome to the Reversi amazing multi-threaded server Ver 0.5" << endl;
	cout << "------------------------------------------------------------" << endl;
	Server server;
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Couldn't start server. Reason: " << msg << endl;
		exit(-1);
	}
	cout << "type \"exit\" at any time to close the server" << endl << endl;
	std::string input;
	bool quit = false;
	do {
		getline(cin,input);
		if (input!="exit")
			cout << "unknown command: " << input << endl;
		else
			quit = true;
	} while(!quit);

	server.stop();

	return 0;
}