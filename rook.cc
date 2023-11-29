#include <vector>
#include "rook.h"

bool Rook::isValidMove(ChessPiece &dest) override {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    // piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // piece is not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // either row or column must be the same, but not both
    if (srcRow != destRow && srcColumn != destColumn) return false;
    // valid move
    return true;
}

vector<ChessSquare> Rook::generatePath(ChessPiece &dest) override {
    vector<ChessSquare> path;
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    if(srcRow == destRow) { // rook moved on same row
        // if srcColumn < destColumn is true, the rook moved to right and left otherwise
        int start = srcColumn < destColumn ? srcColumn + 1 : srcColumn - 1;
        int end = destColumn;
        // if start < end is true, the rook moved to right and left otherwiese
        int step = start < end ? 1 : -1;
        for (int c = start; c != end; c += step) {
            path.emplace_back(srcRow, c);
        }
    } else { // rook moved on same Column
        // if srcRow < destRow  is true, the rook moved to up and down otherwise
        int start = srcRow < destRow ? srcRow + 1 : srcRow - 1;
        int end = destRow;
        // if start < end is true, the rook moved to up and down otherwiese
        int step = start < end ? 1 : -1;
        for (int r = start; r != end; r += step) {
            path.emplace_back(r, srcColumn);
        }
    }

    return path;
}