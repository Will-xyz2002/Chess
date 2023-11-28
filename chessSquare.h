#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H
class ChessSquare {
    int row;
    int column;

public:
    ChessSquare (int r, int c);
    int getRow();
    int getColumn();
    void setCoords(const int row, const int column);
};
#endif
