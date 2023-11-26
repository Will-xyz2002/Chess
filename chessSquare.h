#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H
class ChessSquare {
    int row;
    int column;
    bool empty;

public:
    ChessSquare (int r, int c, bool empty);
    int getRow();
    int getColumn();
    bool isEmpty();
    void setCoords(const int row, const int column);
    void setEmpty(bool empty);
};
#endif
