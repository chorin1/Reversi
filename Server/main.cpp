//
// Created by nitaihalle on 12/6/17.
//
#include <iostream>
#include "Server.h"
#include <stdlib.h>

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