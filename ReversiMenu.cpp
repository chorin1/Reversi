//
// Created by chorin on 11/22/17.
//

#include "ReversiMenu.h"
#include "GameModel.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Controller.h"
#include "ConsoleView.h"
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

static void ReversiMenu::beginGame() {
    GameModel model;
    ConsoleView view(model);
    HumanPlayer p1;
    Player *p2;
    if (choice == PVC)
        p2 = new AIPlayer();
    else
        p2 = new HumanPlayer();
    Controller controller(model, view, p1, *p2);
    controller.beginGame();
    delete p2;
}

static void ReversiMenu::selectFromMenu() {

    cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
    cout << "------------------------------------------" << endl << endl;
    cout << "Please select form the following options:" << endl;
    cout << "1. Play against a human player." << endl;
    cout << "2. Play against an AI player." << endl << endl;
    cout << "choice: ";

    ReversiMenu::GameChoice chosenGame = getMenuChoice();
    ReversiMenu::choice = chosenGame;
        

}



static ReversiMenu::GameChoice ReversiMenu::getMenuChoice() {
    std::string input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid choice. Please try again: ";
        } else {
            std::cin.ignore(32767, '\n');
            if (input.length() == 1 &&
                ((input.find('1') != std::string::npos || input.find('2') != std::string::npos))) {
                return atoi(input.c_str());
            } else
                cout << "Invalid choice. Please try again: ";
        }

    }
}