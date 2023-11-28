#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"

class Queen: public ChessPiece {
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
