#ifndef EMPTY_H
#define EMPTY_H
#include "chessPiece.h"

class Empty: public ChessPiece {
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
