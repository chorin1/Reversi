/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #5
 *  Server main
 */

#include <iostream>
#include <string>
#include "Server.h"
#include <stdlib.h>
using std::cout;
using std::endl;

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

    cout << "type \"exit\" at any time to close the server" << endl;
    std::string input;
    bool quit = false;
    do {
        std::getline(std::cin,input);
        if (input!="exit")
            cout << "unknown command: " << input << endl;
        else
            quit = true;
    } while(!quit);

    server.stop();

    return 0;
}