#include "HumanPlayer.h"
#include <iostream>
#include <cctype>
#include <string>
using std::cin;
using std::cout;
using std::endl;

GameModel::Pos HumanPlayer::makeMove() const {

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
			std::cin.ignore(32767, '\n'); 

			std::string xCoord = input.substr(0, input.find(','));
			std::string yCoord = input.substr(input.find(',') + 1);

			//test if any of the coord length are too big
			if (xCoord.length() == 0 || xCoord.length() > 2 || yCoord.length() == 0 || yCoord.length() > 2) {
				std::cout << "Invalid input. Please try again: ";
				continue;
			}
			int xCoordInt = atoi(xCoord.c_str());
			int yCoordInt = atoi(yCoord.c_str());
			
			//test for possible integers
			if (xCoordInt < 1 || xCoordInt > 30 || yCoordInt < 1 || yCoordInt > 30) {
				std::cout << "Invalid input. Please try again: ";
				continue;
			}
			return GameModel::Pos(xCoordInt, yCoordInt);
		}

	}
}
