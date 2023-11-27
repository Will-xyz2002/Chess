#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer(ChessColour colour);
    void makeAMove() override;
    void resign() override;
};
#endif
