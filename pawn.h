#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Pawn: public ChessPiece {
    bool enPassanted = false;

public:
    Pawn(ChessColour colour, ChessSquare coords);
    bool isEnPassanted();
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
