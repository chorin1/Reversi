/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #4
 *  Group: 04
 *  Date: 27/11/17
 */

#include "../include/ReversiMenu.h"
#include <iostream>

int main() {
    while (ReversiMenu::m_choice != 0) {
        ReversiMenu::selectFromMenu();
        ReversiMenu::beginGame();
        std::cin.get();
    }
    return 0;
}




