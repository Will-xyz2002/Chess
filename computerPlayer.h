#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.h"

class ComputerPlayer: public Player {
    int level;
public:
    ComputerPlayer(ChessColour colour, int level);
    ComputerPlayer(const ComputerPlayer &other) = delete;
    ComputerPlayer &operator=(const ComputerPlayer &other) = delete;
    ~ComputerPlayer() = default;
    void makeAMove() override;
};

#endif
