#include <vector>
#include "queen.h"

Queen::Queen(ChessColour colour, ChessSquare coords)
    : ChessPiece{ChessType::Queen, colour, coords, false} {
    if (colour == ChessColour::White) setDisplay('Q');
    else if (colour == ChessColour::Black) setDisplay('q');
}

bool Queen::isValidMove(ChessPiece &dest) {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();
    int rowMove = ChessPiece::abs(destRow - srcRow); // vertical displacement
    int colMove = ChessPiece::abs(destColumn - srcColumn); // horizontal displacement

    // Check if piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // Check if piece has not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // Check if piece has straight or diagonal move
    if ((srcRow == destRow) || (srcColumn == destColumn) || (rowMove == colMove)) {
        return true;
    }
    // invalid move
    return false;
}

vector<ChessSquare> Queen::generatePath(ChessPiece &dest) {
    vector<ChessSquare> path;
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();

    // vertical Direction: 
    // if srcRow < destRow is true, Bishop moved up and down otherwise
    int rowDict = (srcRow < destRow) ? 1 : -1;
    // horizontal Direction:
    // if srcColumn < destColumn is true, Bishop moved right and left otherwise
    int colDict = (srcColumn < destColumn) ? 1 : -1;

    if (srcRow == destRow) { // Horizontal move
        for (int c = srcColumn + colDict; c != destColumn; c += colDict) {
            path.emplace_back(srcRow, c);
        }
    } else if (srcColumn == destColumn) { // Vertical move
        for (int r = srcRow + rowDict; r != destRow; r += rowDict) {
            path.emplace_back(r, srcColumn);
        }
    } else { // Diagonal move
        for (int r = srcRow + rowDict, c = srcColumn + colDict; 
            r != destRow && c != destColumn; r += rowDict, c += colDict) {
            path.emplace_back(r, c);
        }
    }

    return path;
}
