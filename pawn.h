#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"

class Pawn: public ChessPiece {
    bool enPassant = false;
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
    void promotion();
};

#endif
