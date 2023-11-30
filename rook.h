#ifndef ROOK_H
#define ROOK_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Rook: public ChessPiece {

public:
    Rook(ChessColour colour, ChessSquare coords);
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
