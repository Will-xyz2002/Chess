#ifndef PLAYER_H
#define PLAYER_H

#include "chessPiece.h"
class Player {
    ChessColour colour;
public:
    Player(ChessColour colour);
    virtual void makeAMove();
    virtual void resign();
};
#endif
