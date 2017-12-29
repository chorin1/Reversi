/*
 *  Reversi - Advanced Programming 1
 *  By Nitai Halle & Ben Chorin
 *  Ex: #5
 *  Game main
 */

#include "../include/GameMaker.h"

int main() {
	GameMaker game;
	do  {
		game.mainMenuSelection();
		game.beginGame();
	} while (game.m_choice != GameMaker::GAME_TYPE_EXIT);
	return 0;
}