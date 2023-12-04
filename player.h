#ifndef PLAYER_H
#define PLAYER_H

#include "chessPiece.h"


class Player {
    ChessColour colour;
public:
    Player(ChessColour colour);
    virtual ~Player() = 0;
};

#endif
