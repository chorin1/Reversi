//
// Assuming AI always plays as 'O' = player2
//

#pragma once
#include "Player.h"

class AIPlayer : public Player {
public:
    AIPlayer() {};
    ~AIPlayer() {};
    //returns the position using minimax AI method
    GameModel::Pos makeMove(const GameModel* const model) const;
private:
    int maxOpponentMoveScore(const GameModel* const model) const;

};

