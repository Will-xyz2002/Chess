#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.h"
#include <cstdlib>

class ComputerPlayer: public Player {
    int level;
public:
    ComputerPlayer(ChessColour colour, int level);
    ComputerPlayer(const ComputerPlayer &other) = delete;
    ComputerPlayer &operator=(const ComputerPlayer &other) = delete;
    bool isHuman() override;
    ChessMove generateMove(vector<ChessMove> pool) override;
    ~ComputerPlayer() = default;
};

#endif
