/*
*  Client.cpp
*
*/

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include "../include/Client.h"
using std::cout;
using std::endl;
using std::string;

//must set static members globally
const GameModel::Pos Client::noMovePos = GameModel::Pos(-5,-5);
const GameModel::Pos Client::endGamePos = GameModel::Pos(-1,-1);

Client::Client() {
	const char* serverIP;
	int port;

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

	//TODO: delete cout
	std::cout << "creating client with -> " << serverIP << ":" << port << endl;

	this->serverIP = serverIP;
	this->serverPort = port;
	clientSocket = 0;
}

Client::Client(const char *serverIP, int serverPort):
		serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}

void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		throw "Error opening socket";

	//convert IP to network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address))
		throw "Can't parse IP address";
	struct hostent *server;
	server = gethostbyaddr((const void* )&address, sizeof(address), AF_INET);
	if (server==NULL)
		throw "Host is unreachable";

	struct sockaddr_in serverAddress;
	bzero((char*)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		throw "Error connecting to server";
	//TODO: delete cout
	cout << "Connected to server!" << endl;

}

int Client::getClientPlayerNum() {
	int clientsPlayerNum = 0;
	int n = read(clientSocket, &clientsPlayerNum, sizeof(clientsPlayerNum));
	if (n == -1)
		throw "Error reading player num from socket";
	return clientsPlayerNum;
}

GameModel::Pos Client::getMove() {
	GameModel::Pos pos(0, 0);
	int n = read(clientSocket, &pos, sizeof(pos));
	if (n == -1)
		throw "Error getting position from socket";
	if (n == 0)
		throw "Disconnected from server";
	//TODO: delete cout later
	cout << "Got from server move: " << pos.m_x << ", " << pos.m_y << endl;
	return pos;
}

void Client::sendMove(GameModel::Pos pos) {
	int n = write(clientSocket, &pos, sizeof(pos));
	if (n==-1)
		throw "Error sending move to socket";
	if (n == 0)
		throw "Disconnected from server";
	//TODO: delete cout later
	cout << "Sent to server move: " << pos.m_x << ", " << pos.m_y << endl;
}

void Client::disconnect() {
	close(clientSocket);
}

