#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.h"

class ComputerPlayer: public Player {
    int level;
public:
    ComputerPlayer(ChessColour colour, int level);
    void makeAMove() override;
};

#endif
