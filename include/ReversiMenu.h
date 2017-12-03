/**
*  Reversi - Advanced Programming 1
*  Ex: #3
*  Group: 04
*  Main menu for game reversi.
*  Shows the menu in the console and creates the game (controller, players and model)
*  according to the user choice.
*/

#pragma once

class ReversiMenu {
private:
    enum GameType {
        PVP = 1,
        PVC,
        NETWORK_GAME,
        GAMETYPE_COUNT
    };
public:
    static GameType m_choice;
    static void selectFromMenu();
    static void beginGame();
private:
    static GameType getMenuChoice();
};



