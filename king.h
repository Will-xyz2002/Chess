#ifndef KING_H
#define KING_H
#include "chessPiece.h"

class King: public ChessPiece {
    bool isChecked;
    bool isCastled;
    std::vector<ChessSquare> generatePath(ChessPiece &dest) override;
public:
    bool isValidMove(ChessPiece &dest) override;
    bool isPathClear(ChessPiece &dest) override;
};

#endif
