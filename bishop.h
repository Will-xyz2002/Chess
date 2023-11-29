#ifndef BISHOP_H
#define BISHOP_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Bishop: public ChessPiece {

public:
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
