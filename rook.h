#ifndef ROOK_H
#define ROOK_H
#include "chessPiece.h"

class Rook: public ChessPiece {
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
