#include <vector>
#include "bishop.h"

bool Bishop::isValidMove(ChessPiece &dest) override {
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
    // Check if piece has diagonal move
    if (rowMove == colMove) return true;
    // invalid move
    return false;
}

vector<ChessSquare> Bishop::generatePath(ChessPiece &dest) override {
    vector<ChessSquare> path;
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    // vertical Direction: 
    // if srcRow < destRow is true, Bishop moved up and down otherwise
    int rowDict = srcRow < destRow ? 1 : -1;
    // horizontal Direction:
    // if srcColumn < destColumn is true, Bishop moved right and left otherwise
    int colDict = srcColumn < destColumn ? 1 : -1;

    // diagonal move: row and column get one diagonal step closer to destination
    for(int r = srcRow + rowDict, c = srcColumn + colDict;
        r != destRow && c != destColumn; r += rowDict, c += colDict) {
        path.emplace_back(r, c);
    }
    
    return path;
}
