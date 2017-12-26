//
// Created by chorin on 12/26/17.
//

#pragma once

#include <iostream>
#include <map>
#include "GameSession.h"

// singleton class containing the gamelist
class GameList {
public:
    static GameList& getInstance() {
        static GameList instance; // static singleton, guaranteed to be destroyed
        return instance;
    }
private:
    std::map <std::string, GameSession*> m_gameSessionMap;
    GameList() {};
    GameList(const GameList&) {} // Prevent construction by copying
    GameList& operator=(const GameList&) {} // Prevent assignment
    ~GameList() {} // Prevent unwanted destruction
};