/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #4
 *  Game main
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