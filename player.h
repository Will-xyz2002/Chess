#ifndef PLAYER_H
#define PLAYER_H

#include "chessPiece.h"
#include "chessMove.h"


class Player {
    ChessColour colour;
public:
    Player(ChessColour colour);
    virtual bool isHuman() = 0;
    virtual ChessMove generateMove(vector<ChessMove> pool) = 0;
};

#endif
