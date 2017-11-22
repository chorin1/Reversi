//
// Created by chorin on 11/22/17.
//

#pragma once


class ReversiMenu {
private:
    enum GameChoice {
        PVP,
        PVC
    };
public:
    static void selectFromMenu();
    static void beginGame();
private:
    static GameChoice choice;
    static ReversiMenu::GameChoice getMenuChoice()
};



