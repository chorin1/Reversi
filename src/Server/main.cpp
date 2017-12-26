/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #4
 *  Server main
 */

#include <iostream>
#include "Server.h"
#include <stdlib.h>
#include "GameList.h"
using std::cout;
using std::endl;

int main() {
    try {
		Server server;
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(1);
    }
    return 0;
}