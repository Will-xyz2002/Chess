#include <vector>
#include "knight.h"

bool Knight::isValidMove(ChessPiece &dest) override {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();
    int rowMove = ChessPiece::abs(destRow - srcRow); // vertical change
    int colMove = ChessPiece::abs(destColumn - srcColumn); // horizontal change

    // Check if piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // Check if piece has not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // Check if L move is valid
    if(rowMove == 1 && colMove == 2) return true; 
    if(rowMove == 2 && colMove == 1) return true;
    // invalid move
    return false;
}

vector<ChessSquare> Knight::generatePath(ChessPiece &dest) override {
    vector<ChessSquare> path;
    return path;
}
