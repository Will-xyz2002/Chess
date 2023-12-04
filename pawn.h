#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Pawn: public ChessPiece {
public:
    Pawn(ChessColour colour, ChessSquare coords);
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
