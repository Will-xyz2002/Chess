#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"

class Knight: public ChessPiece {
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
