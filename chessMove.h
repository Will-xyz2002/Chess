#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H
#include "chessPiece.h"
#include <iostream>

class ChessMove {
    ChessPiece initial;
    ChessPiece dest;
public:
    ChessMove(ChessPiece &initial, ChessPiece &dest);
    ChessPiece getInitial();
    ChessPiece getDest();
};
#endif
