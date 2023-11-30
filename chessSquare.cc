#include "chessSquare.h"

ChessSquare::ChessSquare (int r, int c): row{r}, column{c} {}

int ChessSquare::getRow() { return row; }
int ChessSquare::getColumn() { return column; }
void ChessSquare::setCoords(const int row, const int column) {
    this->row = row;
    this->column = column;
}
    