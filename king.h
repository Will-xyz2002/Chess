#ifndef KING_H
#define KING_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class King: public ChessPiece {
    bool isChecked;
    bool isCastled;

public:
    King(ChessColour colour, ChessSquare coords);
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
