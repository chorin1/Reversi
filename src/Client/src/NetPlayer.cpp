//
// Created by chorin on 12/4/17.
//

#include <iostream>
#include "../include/NetPlayer.h"

using std::cout;
using std::endl;

void NetPlayer::sendMove(GameModel::Pos pos) const {
	try {
		m_client->sendMove(pos);
	} catch (const char *msg) {
		throw;
	}
}

GameModel::Pos NetPlayer::makeMove(const GameModel*) const {
	GameModel::Pos pos(0,0);
	cout << "Waiting for other player's move..." << endl;
	try {
		pos = m_client->getMove();
	} catch (const char* msg) {
		throw;
	}
	return pos;
}
