/*
*  HumanPlayer.cpp
*
*/

#include "../include/HumanPlayer.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include "../include/GameModel.h"

using std::cin;
using std::cout;
using std::endl;

GameModel::Pos HumanPlayer::makeMove(const GameModel*) const {

	std::string input;

	while (true) {
		cin >> input;

		//cin failed or couldn't find ','
		if (std::cin.fail() || input.find(',') == std::string::npos) {
			std::cin.clear();
			std::cin.ignore(32767, '\n'); 
			std::cout << "Invalid input. Please try again: ";
		}
		else
		{
			//drop all overbuffered data
			std::cin.ignore(32767, '\n'); 

			std::string xCoord = input.substr(0, input.find(','));
			std::string yCoord = input.substr(input.find(',') + 1);

			//test if any of the coord length are too big
			if (xCoord.length() == 0 || xCoord.length() > 2 || yCoord.length() == 0 || yCoord.length() > 2) {
				std::cout << "Invalid input. Please try again: ";
				continue;
			}

			//convert coord to integer
			int xCoordInt = atoi(xCoord.c_str());
			int yCoordInt = atoi(yCoord.c_str());
			
			//are the integers valid?
			if (xCoordInt < 1 || xCoordInt > GameModel::MAX_BOARD_SIZE ||
				yCoordInt < 1 || yCoordInt > GameModel::MAX_BOARD_SIZE) {
				std::cout << "Invalid input. Please try again: ";
				continue;
			}
			return GameModel::Pos(xCoordInt, yCoordInt);
		}

	}
}
