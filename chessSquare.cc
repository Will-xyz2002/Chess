#include "chessSquare.h"

ChessSquare::ChessSquare (int r, int c, bool empty)
    : row{r}, column{c} {}

int ChessSquare::getRow() { return row; }
int ChessSquare::getColumn() { return column; }
void ChessSquare::setCoords(const int row, const int column)
    : row{row}, column{column} {}
    