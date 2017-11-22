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

using std::cin;
using std::cout;
using std::endl;

//must set static members globally
ReversiMenu::GameType ReversiMenu::m_choice = PVP;

void ReversiMenu::beginGame() {
    GameModel model;
    ConsoleView view(model);
    HumanPlayer p1;
    Player *p2;
    if (m_choice == PVC) {
        p2 = new AIPlayer();
        cout << "Starting a game vs AI..." << endl << endl;
    } else {
        p2 = new HumanPlayer();
        cout << "Starting a PVP game..." << endl << endl;
    }
    Controller controller(model, view, p1, *p2);
    controller.beginGame();
    delete p2;
}

void ReversiMenu::selectFromMenu() {

    cout << "      ~ Welcome to Reversi\\Othello ~     " << endl;
    cout << "         -A Game By Nathan & Ben-     " << endl;
    cout << "------------------------------------------" << endl << endl;
    cout << "Please select form the following options:" << endl;
    cout << "1. Play against a human player." << endl;
    cout << "2. Play against an AI player." << endl << endl;
    cout << "choice: ";

    m_choice = getMenuChoice();

}

ReversiMenu::GameType ReversiMenu::getMenuChoice() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid choice. Please try again: ";
        } else {
            std::cin.ignore(32767, '\n');
            if (input >= 1 && input < GAMETYPE_COUNT) {
                return static_cast<ReversiMenu::GameType>(input);
            } else
                cout << "Invalid choice. Please try again: ";
        }

    }
}