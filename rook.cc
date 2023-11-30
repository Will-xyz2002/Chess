#include <vector>
#include "rook.h"

Rook::Rook(ChessColour colour, ChessSquare coords): ChessPiece{ChessType::Rook, colour, coords, false} {
    if (colour == ChessColour::White) setDisplay('R');
    else if (colour == ChessColour::Black) setDisplay('r');
}

bool Rook::isValidMove(ChessPiece &dest) {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    // Check if piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // Check if piece has not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // Check if piece has straight move
    if (srcRow == destRow || srcColumn == destColumn) return true;
    // valid move
    return false;
}

vector<ChessSquare> Rook::generatePath(ChessPiece &dest) {
    vector<ChessSquare> path;
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    if(srcRow == destRow) { // rook moved on same row
        // if srcColumn < destColumn is true, rook moved to right and left otherwise
        int start = srcColumn < destColumn ? srcColumn + 1 : srcColumn - 1;
        int end = destColumn;
        // if start < end is true, rook moved to right and left otherwiese
        int step = start < end ? 1 : -1;
        for (int c = start; c != end; c += step) {
            path.emplace_back(srcRow, c);
        }
    } else { // rook moved on same Column
        // if srcRow < destRow  is true, rook moved to up and down otherwise
        int start = srcRow < destRow ? srcRow + 1 : srcRow - 1;
        int end = destRow;
        // if start < end is true, rook moved to up and down otherwiese
        int step = start < end ? 1 : -1;
        for (int r = start; r != end; r += step) {
            path.emplace_back(r, srcColumn);
        }
    }

    return path;
}
