#include <vector>
#include "knight.h"

bool Knight::isValidMove(ChessPiece &dest) override {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();
    int rowMove = ChessPiece::abs(destRow - srcRow); // change by vertical move
    int colMove = ChessPiece::abs(destColumn - srcColumn); // change by horizontal move

    // piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // piece is not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // valid L moves
    if(rowMove == 1 && colMove == 2) return true; 
    else if(rowMove == 2 && colMove == 1) return true;
    else return false; // invalid move
}
