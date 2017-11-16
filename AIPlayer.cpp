//
// Created by chorin on 11/16/17.
//

#include "AIPlayer.h"
#include <cassert>
#include <climits>

GameModel::Pos AIPlayer::makeMove(const GameModel* const model) const {
    //get possible moves of player2 (computer)
    GameModel::Pos bestCPUMove(0,0);
    int minOpponentScore = INT_MAX;
    const std::vector<GameModel::Pos>* vec = model->getPossibleMoves(GameModel::PLAYER2);
    for (std::vector<GameModel::Pos>::const_iterator cpuMove = vec->begin(); cpuMove != vec->end(); ++cpuMove) {
        GameModel copyModel(*model);
        copyModel.place(GameModel::PLAYER2, *cpuMove);
        int tempScore = maxOpponentMoveScore(&copyModel);
        if (tempScore < minOpponentScore) {
            minOpponentScore = tempScore;
            bestCPUMove = *cpuMove;
        }
    }
    return bestCPUMove;
}

int AIPlayer::maxOpponentMoveScore(const GameModel *const model) const {
    int maxScore = INT_MIN;
    //get possible moves of player 1 (human)
    const std::vector<GameModel::Pos>* vec = model->getPossibleMoves(GameModel::PLAYER1);
    for (std::vector<GameModel::Pos>::const_iterator it = vec->begin(); it != vec->end(); ++it) {
        //create a copy of the model and try each move
        GameModel tempModel(*model);
        assert (tempModel.place(GameModel::PLAYER1,*it));
            int tempScore = tempModel.calcScoreOf(GameModel::PLAYER1) -
                            tempModel.calcScoreOf(GameModel::PLAYER2);
            if (tempScore > maxScore)
                maxScore = tempScore;
    }
    return maxScore;
}
