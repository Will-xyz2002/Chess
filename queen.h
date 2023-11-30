#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Queen: public ChessPiece {

public:
    Queen(ChessColour colour, ChessSquare coords);
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
