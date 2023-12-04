#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer(ChessColour colour);
    bool isHuman() override;
    HumanPlayer(const HumanPlayer &other) = delete;
    HumanPlayer &operator=(const HumanPlayer &other) = delete;
    ~HumanPlayer() = default;
};
#endif
