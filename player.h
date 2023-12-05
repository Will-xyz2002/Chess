#ifndef PLAYER_H
#define PLAYER_H

#include "chessPiece.h"
#include "chessMove.h"
#include "chessBoard.h"
#include <algorithm>  // For std::copy
#include <iterator> 

class Player {
    ChessColour colour;
public:
    Player(ChessColour colour);
    virtual bool isHuman() = 0;
    ChessColour getColour();
    virtual ChessMove generateMove(ChessBoard &board) = 0;
};

#endif
