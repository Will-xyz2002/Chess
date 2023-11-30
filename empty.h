#ifndef EMPTY_H
#define EMPTY_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Empty: public ChessPiece {

public:
    Empty(ChessSquare coords);
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
};

#endif
