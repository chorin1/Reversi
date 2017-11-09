//
// Created by chorin on 11/6/17.
//

#include "GameModel.h"
#include <algorithm>

GameModel::GameModel() {
   m_board = new Board(DEFAULT_BOARD_SIZE);
}

GameModel::~GameModel() {
    delete GameModel::m_board;
}


bool GameModel::isOutOfBounds (const Pos& pos) const {
    int boardSize = GameModel::getBoardSize();
    if (pos.m_x < 1 || pos.m_y < 1 || pos.m_x > boardSize || pos.m_y > boardSize)
        return true;
    return false;
}

Board::Cell GameModel::getCellAt(const Pos& pos) const
{
    if (GameModel::isOutOfBounds(pos)) {
        return Board::CELL_ERROR;
    }
    return GameModel::m_board->getCellAt(pos.m_x-1,pos.m_y-1); //conversion from board to array
}

const std::vector<GameModel::Pos>* GameModel::getPossibleMoves(PlayerNum player) const {
    return (player==PLAYER1)? &m_possibleMovesPlayer1 : &m_possibleMovesPlayer2;
}

bool GameModel::isPossibleMove (const PlayerNum& player, const Pos& pos) const {
    const std::vector<Pos>* vec = (player==PLAYER1)? &m_possibleMovesPlayer1 : &m_possibleMovesPlayer2;
    if (std::find(vec->begin(), vec->end(), pos) != vec->end())
        return true;
    return false;
}

bool GameModel::place (const PlayerNum& player, const Pos& pos) {
    if (!isPossibleMove(player, pos))
        return false;
    Board::Cell currPiece;
    Board::Cell opponentPiece;
    switch (player) {
        case PLAYER1:
            currPiece = Board::CELL_PLAYER1;
            opponentPiece = Board::CELL_PLAYER2;
            break;
        case PLAYER2:
        default:
            currPiece = Board::CELL_PLAYER2;
            opponentPiece = Board::CELL_PLAYER1;
            break;
    }
    setCellAt(pos, currPiece); //set current cell to player piece
    int row = pos.m_x;
    int clmn = pos.m_y;
    bool south = false;
    bool north = false;
    bool east = false;
    bool west = false;
    bool nw = false;
    bool ne = false;
    bool sw = false;
    bool se = false;

    //goTo (direction, currplayerpiece, nextposition, flipIfValidMove, false
    south = goTo(SOUTH, currPiece, Pos(row+1, clmn), true, false);
    north = goTo(NORTH, currPiece, Pos(row-1, clmn), true, false);
    east = goTo(EAST, currPiece, Pos(row, clmn+1), true, false);
    west = goTo(WEST, currPiece, Pos(row, clmn-1), true, false);
    nw = goTo(NW, currPiece, Pos(row-1, clmn-1), true, false);
    ne = goTo(NE, currPiece, Pos(row-1, clmn+1), true, false);
    sw = goTo(SW, currPiece, Pos(row+1, clmn-1), true, false);
    se = goTo(SE, currPiece, Pos(row+1, clmn+1), true, false);

    return (north || south || east || west || nw || ne || sw || se);

}

void GameModel::updatePossibleMoves(PlayerNum& player) {
    std::vector<Pos>* vec;
    Board::Cell currPiece;
    Board::Cell opponentPiece;
    switch (player) {
        case PLAYER1:
            vec = &m_possibleMovesPlayer1;
            currPiece = Board::CELL_PLAYER1;
            opponentPiece = Board::CELL_PLAYER2;
            break;
        case PLAYER2:
        default:
            vec = &m_possibleMovesPlayer2;
            currPiece = Board::CELL_PLAYER2;
            opponentPiece = Board::CELL_PLAYER1;
            break;
    }

    vec->clear();
    for (int row = 1; row <= getBoardSize(); row++) {
        for (int clmn = 1; clmn <= getBoardSize(); clmn++) {
            Pos currPos(row,clmn);
            bool south = false;
            bool north = false;
            bool east = false;
            bool west = false;
            bool nw = false;
            bool ne = false;
            bool sw = false;
            bool se = false;

            if (getCellAt(currPos) == Board::CELL_EMPTY) { //ok, current cell is empty, check adjacent cells
                south = goTo(SOUTH, currPiece, Pos(row+1, clmn), false, false);
                north = goTo(NORTH, currPiece, Pos(row-1, clmn), false, false);
                east = goTo(EAST, currPiece, Pos(row, clmn+1), false, false);
                west = goTo(WEST, currPiece, Pos(row, clmn-1), false, false);
                nw = goTo(NW, currPiece, Pos(row-1, clmn-1), false, false);
                ne = goTo(NE, currPiece, Pos(row-1, clmn+1), false, false);
                sw = goTo(SW, currPiece, Pos(row+1, clmn-1), false, false);
                se = goTo(SE, currPiece, Pos(row+1, clmn+1), false, false);
            }
            if (north || south || east || west || nw || ne || sw || se)
                vec->push_back(currPos);
        }
    }

}

bool GameModel::isAbleToMove(PlayerNum& player) const {
    const std::vector<Pos>* vec = (player==PLAYER1)? &m_possibleMovesPlayer1 : &m_possibleMovesPlayer2;
    return !(vec->empty());
}

void GameModel::setCellAt(const Pos& pos, const Board::Cell piece) {
    if (isOutOfBounds(pos))
        std::cout << "error in GameModel::setCell, out of bounds" << std::endl;
    else
        m_board->setCellValue(pos.m_x-1, pos.m_y-1, piece);
}


/*
bool GameModel::goDown(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found) {
    Board::Cell currCell = getCellAt(pos);
    if (currCell==Board::CELL_ERROR || currCell == Board::CELL_EMPTY) //reached out of bounds or an empty cell
        return false;
    if (currCell==currPlayerPiece)
       if (!found)
           return false;
        if (found)
            return true;
    if (goDown(currPlayerPiece, Pos(pos.m_x+1, pos.m_y), doFlip, true)) { //current cell contains opponent
        if (doFlip)
            flip(pos);
        return true;
    }
    return false;
}

bool GameModel::goUp(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found) {
    Board::Cell currCell = getCellAt(pos);
    if (currCell==Board::CELL_ERROR || currCell == Board::CELL_EMPTY) //reached out of bounds or an empty cell
        return false;
    if (currCell==currPlayerPiece)
        if (!found)
            return false;
    if (found)
        return true;
    if (goUp(currPlayerPiece, Pos(pos.m_x-1, pos.m_y), doFlip, true)) { //current cell contains opponent
        if (doFlip)
            flip(pos);
        return true;
    }
    return false;
}

bool GameModel::goLeft(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found) {
    Board::Cell currCell = getCellAt(pos);
    if (currCell==Board::CELL_ERROR || currCell == Board::CELL_EMPTY) //reached out of bounds or an empty cell
        return false;
    if (currCell==currPlayerPiece)
        if (!found)
            return false;
    if (found)
        return true;
    if (goLeft(currPlayerPiece, Pos(pos.m_x, pos.m_y-1), doFlip, true)) { //current cell contains opponent
        if (doFlip)
            flip(pos);
        return true;
    }
    return false;
}

bool GameModel::goRight(const Board::Cell& currPlayerPiece, const Pos pos, bool doFlip, bool found) {
    Board::Cell currCell = getCellAt(pos);
    if (currCell==Board::CELL_ERROR || currCell == Board::CELL_EMPTY) //reached out of bounds or an empty cell
        return false;
    if (currCell==currPlayerPiece)
        if (!found)
            return false;
    if (found)
        return true;
    if (goRight(currPlayerPiece, Pos(pos.m_x, pos.m_y+1), doFlip, true)) { //current cell contains opponent
        if (doFlip)
            flip(pos);
        return true;
    }
    return false;
}
*/
//START of experimental
bool GameModel::goTo (const GameModel::Direction& direction, const Board::Cell& currPlayerPiece, const Pos& pos, const bool& doFlip, bool found) {
    Board::Cell currCell = getCellAt(pos);
    if (currCell==Board::CELL_ERROR || currCell == Board::CELL_EMPTY) //reached out of bounds or an empty cell
        return false;
    if (currCell==currPlayerPiece) {
        if (!found)
            return false;
        if (found)
            return true;
    }
    Pos nextPos(1,1);
    switch (direction) {
        case NORTH:
            nextPos.m_x = pos.m_x-1;
            nextPos.m_y = pos.m_y;
            break;
        case SOUTH:
            nextPos.m_x = pos.m_x+1;
            nextPos.m_y = pos.m_y;
            break;
        case EAST:
            nextPos.m_x = pos.m_x;
            nextPos.m_y = pos.m_y+1;
            break;
        case WEST:
            nextPos.m_x = pos.m_x;
            nextPos.m_y = pos.m_y-1;
            break;
        case NW:
            nextPos.m_x = pos.m_x-1;
            nextPos.m_y = pos.m_y-1;
            break;
        case NE:
            nextPos.m_x = pos.m_x-1;
            nextPos.m_y = pos.m_y+1;
            break;
        case SW:
            nextPos.m_x = pos.m_x+1;
            nextPos.m_y = pos.m_y-1;
            break;
        case SE:
            nextPos.m_x = pos.m_x+1;
            nextPos.m_y = pos.m_y+1;
            break;
        default:
            nextPos.m_x = 0;
            nextPos.m_y = 0;
            break;
        }
    if (goTo(direction, currPlayerPiece, nextPos, doFlip, true)) { //current cell contains opponent
        if (doFlip)
            flip(pos);
        return true;
    }
    return false;
}

//END OF EXPERIMENTAL

void GameModel::flip(const Pos& pos) {
    Board::Cell currPiece = getCellAt(pos);
    if (currPiece==Board::CELL_ERROR || currPiece == Board::CELL_EMPTY) {
        std::cout << "Error in GameModel::flip, trying to flip an empty/undefined cell" << std::endl;
        return;
    }
    if (currPiece==Board::CELL_PLAYER1)
        setCellAt(pos, Board::CELL_PLAYER2);
    else
        setCellAt(pos, Board::CELL_PLAYER1);

}


