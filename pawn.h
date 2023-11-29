#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include "chessPiece.h"

using namespace std;

class Pawn: public ChessPiece {
    bool enPassant = false;

public:
    bool isValidMove(ChessPiece &dest) override;
    vector<ChessSquare> generatePath(ChessPiece &dest) override;
    void promotion();
};

#endif
