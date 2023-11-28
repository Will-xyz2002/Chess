#ifndef BISHOP_H
#define BISHOP_H
#include "chessPiece.h"

class Bishop: public ChessPiece {
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
