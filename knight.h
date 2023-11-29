#ifndef KNIGHT_H
#define KNIGHT_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Knight: public ChessPiece {

public:
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
