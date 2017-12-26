//
// Created by chorin on 12/26/17.
//

#include "GameList.h"

GameList::~GameList() {
    std::map<std::string, GameSession*>::iterator it;
    for (it = gameSessionMap.begin(); it != gameSessionMap.end(); it++) {
        delete it->second;
    }
}
