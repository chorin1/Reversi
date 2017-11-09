//
// Created by chorin on 11/6/17.
//
#include "ConsoleView.h"
#include <iostream>
using std::cout;
using std::endl;

void ConsoleView::drawFirstRow() const {
    cout << " |";
    for (int i=1; i<= m_model->getBoardSize(); i++) {
        cout << " " << i << " |";
    }
    cout << endl;
}

void ConsoleView::drawCompleteLine() const {
    cout << "--";
    for (int i=1; i<= m_model->getBoardSize(); i++) {
        cout << "----";
    }
    cout << endl;

}

void ConsoleView::drawRow(int row) const {
    cout << row << "|";
    for (int i=1; i <= m_model->getBoardSize(); i++) {
        cout << " ";
        GameModel::Pos curr(row,i);
        switch (m_model->getCellAt(curr)) { //(m_model->getCellAt(row, i)
            case Board::CELL_EMPTY:
                cout << " ";
                break;
            case Board::CELL_PLAYER1:
                cout << "X";
                break;
            case Board::CELL_PLAYER2:
                cout << "O";
                break;
            case Board::CELL_ERROR:
            default:
                cout << "E"; //error
                break;
        }

        cout << " |";
    }
    cout << endl;
}

void ConsoleView::DrawBoard() const {
    drawFirstRow();
    drawCompleteLine();
    for (int i=1; i<= m_model->getBoardSize() ; i++) {
        drawRow(i);
        drawCompleteLine();
    }
}


void ConsoleView::drawPossibleMoves (const GameModel::PlayerNum ofPlayer) const {
    const std::vector<GameModel::Pos>* vec = m_model->getPossibleMoves(ofPlayer);
    cout << "Possible moves are:" << endl;
    for (std::vector<GameModel::Pos>::const_iterator it = vec->begin(); it != vec->end(); ++it) {
        cout << "(" << it->m_x << "," << it->m_y << ") ";
    }
}