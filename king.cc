#include <vector>
#include "king.h"

bool King::isValidMove(ChessPiece &dest) override {
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
    // Check for straight or diagonal move by extacly one
    if(srcRow == destRow && colMove != 1) return false; // horizontal move
    else if(srcColumn == destColumn && rowMove != 1) return false; // vertical move
    else if(rowMove != 1 && colMove != 1) return false; // diagonal
    else return true; // valid move
}

vector<ChessSquare> King::generatePath(ChessPiece &dest) override {
    vector<ChessSquare> path;
    return path;
}
