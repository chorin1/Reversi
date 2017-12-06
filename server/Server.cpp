//
// Created by nitaihalle on 12/4/17.
//
#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include<fstream>
using std::string;
using std::cout;
using std::endl;

#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

Server::Server() {
    const char* serverIP;

    std::ifstream configFile;
    configFile.open("config.txt");
    if (!configFile.is_open())
        throw("error opening config.txt");
    string inputStr;
    configFile >> inputStr;
    if (inputStr.find(':') == std::string::npos)
        throw("error parsing config file");

    string serverIPstring = inputStr.substr(0, inputStr.find(':'));
    serverIP = serverIPstring.c_str();

    string serverPortString = inputStr.substr(inputStr.find(':') + 1);
    port = atoi(serverPortString.c_str());

    configFile.close();

}
void Server::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        throw "Error opening socket";
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
        throw "Error binding";

    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    //define client socket structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    while (true) {
        cout << "Waiting for client connections..." << endl;

        // accept a new connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

        cout << "Client1 connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";


        int clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);

        cout << "Client2 connected" << endl;
        if (clientSocket2 == -1)
            throw "Error on accept";
        int send = 1;
        int n = write(clientSocket, &send, sizeof(int));
        if (n==-1) {
            cout << "error reading send" << endl;
            return;
        }
        if (n==0) {
            cout << "client disconnected.." << endl;
            return;
        }
        send = 2;
        n = write(clientSocket2, &send, sizeof(int));
        if (n==-1) {
            cout << "error reading send" << endl;
            return;
        }
        if (n==0) {
            cout << "client disconnected.." << endl;
            return;
        }

        handleClient(clientSocket,clientSocket2);

        //close communication
        close(clientSocket);
        close(clientSocket2);
        cout<<"disconnect"<<endl;

    }

}

void Server::handleClient(int clientSocket,int clientSocket2) {
    Pos pos(0,0);

    while (pos != Pos(-1,-1)) {
        //read new position from client1.
        int n = read(clientSocket, &pos, sizeof(pos));
        if (n==-1) {
            cout << "error reading pos" << endl;
            return;
        }
        if (n==0) {
            cout << "client disconnected.." << endl;
            return;
        }
        if (pos == Pos(-1,-1)){
            return;
        }
        //write to client1
        if ((pos != Pos(-5,-5))&&(pos != Pos(-1,-1))) {
            n = write(clientSocket2, &pos, sizeof(pos));
        }
        n = read(clientSocket2, &pos, sizeof(pos));
        if (n==-1) {
            cout << "error reading pos" << endl;
            return;
        }
        if (n==0) {
            cout << "client disconnected.." << endl;
            return;
        }
        if (pos == Pos(-1,-1)){
            return;
        }
        //write to client2
        if ((pos != Pos(-5,-5))&&(pos != Pos(-1,-1))) {
            n = write(clientSocket, &pos, sizeof(pos));
        }
    }
}
void Server::stop() {
    close(serverSocket);
}
