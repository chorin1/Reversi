//
// Created by nitaihalle on 12/6/17.
//
#include <iostream>
#include "Server.h"
#include <stdlib.h>

using std::cout;
using std::endl;

int main() {
    Server server(8000);
    try {
        server.start();

    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}


