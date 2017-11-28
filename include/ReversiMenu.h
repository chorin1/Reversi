//
// Created by chorin on 11/22/17.
//

#pragma once


class ReversiMenu {
private:
    enum GameType {
        PVP = 1,
        PVC,
        GAMETYPE_COUNT
    };
public:
    static GameType m_choice;
    static void selectFromMenu();
    static void beginGame();
private:
    static GameType getMenuChoice();
};



