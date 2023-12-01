#include "empty.h"

Empty::Empty(ChessSquare coords): ChessPiece{ChessType::Empty, ChessColour::None, coords, true} {
    int sum = coords.getRow() + coords.getColumn();
    if (sum % 2 == 0) setDisplay(' ');
    else setDisplay('_');
}

bool Empty::isValidMove(ChessPiece &dest) {
    return false;
}

vector<ChessSquare> generatePath(ChessPiece &dest) {
    std::vector<ChessSquare> path;
    return path;
}