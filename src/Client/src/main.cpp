/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #4
 *  Game main
 */

#include "../include/GameMaker.h"
#include <iostream>

int main() {
	GameMaker game;
	do  {
		game.mainMenuSelection();
		game.beginGame();
	} while (game.m_choice != GameMaker::GAME_TYPE_EXIT);
	return 0;
}