#include <vector>
#include "pawn.h"

Pawn::Pawn(ChessColour colour, ChessSquare coords)
    : ChessPiece{ChessType::Pawn, colour, coords, false} {
    if (colour == ChessColour::White) setDisplay('P');
    else if (colour == ChessColour::Black) setDisplay('p');
}

bool Pawn::isEnPassanted() { return enPassanted; }

bool Pawn::isValidMove(ChessPiece &dest) {
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();
    // vertical displacement (rowMove forwarded)
    int rowMove = (this->getColour() == ChessColour::White) ? srcRow - destRow : destRow - srcRow;
    int colMove = ChessPiece::abs(destColumn - srcColumn); // horizontal displacement

    // Check if piece is out of board range
    if (!(0 <= srcRow && srcRow <= 7 && 0 <= srcColumn && srcColumn <= 7 &&
          0 <= destRow && destRow <= 7 && 0 <= destColumn && destColumn <= 7)) {
        return false;
    }
    // Check if piece has not moved
    if(srcRow == destRow && srcColumn == destColumn) return false;
    // Check for straight move and diagonal move
    if(rowMove == 1) {
        if(colMove == 0) return true; // one move forward
        else if(colMove == 1 && !dest.isEmpty()) return true; // diagonal move
        else return false;
    } else if(rowMove == 2 && !this->hasMoved()) { // enpassant move
            enPassanted = true;
            return true;
    }
    // invalid move
    return false;
}

vector<ChessSquare> Pawn::generatePath(ChessPiece &dest) {
    vector<ChessSquare> path;
    int srcRow = this->getCoords().getRow();
    int srcColumn = this->getCoords().getColumn();
    int destRow = dest.getCoords().getRow();
    int destColumn = dest.getCoords().getColumn();
    // vertical change (rowMove forwarded)
    int rowMove = (this->getColour() == ChessColour::White) ? srcRow - destRow : destRow - srcRow;

    // enpassant: 2 move forward
    if(srcColumn == destColumn && rowMove == 2) {
        int midRow = (this->getColour() == ChessColour::White) ? srcRow - 1 : srcRow + 1;
        path.emplace_back(midRow, srcColumn);
    }
    
    return path;
}
