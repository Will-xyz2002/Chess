#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer(ChessColour colour);
    HumanPlayer(const HumanPlayer &other) = delete;
    HumanPlayer &operator=(const HumanPlayer &other) = delete;
    ~HumanPlayer() = default;
    void makeAMove() override;
    void resign() override;
};
#endif
