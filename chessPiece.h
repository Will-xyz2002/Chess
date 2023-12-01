#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <vector>
#include "chessSquare.h"

using namespace std;

enum class ChessColour {White, Black, None};
enum class ChessType {Pawn, King, Bishop, Knight, Queen, Rook, Empty};

class ChessPiece {
    ChessType type;
    ChessColour colour;
    ChessSquare coordinate;
    char display;
    bool isMoved = false;
    bool empty;

public:
    ChessPiece(ChessType type, ChessColour colour, ChessSquare coords, bool empty);
    ~ChessPiece();
    ChessPiece(const ChessPiece &other);
    ChessPiece(ChessPiece &&other);
    ChessPiece &operator=(const ChessPiece &other);
    ChessPiece &operator=(ChessPiece &&other);

    // accessors
    ChessColour getColour();
    ChessSquare getCoords();
    ChessType getType();
    char getDisplay();
    bool isEmpty();
    bool hasMoved();

    // settors
    void setColour(ChessColour newColour);
    void setDisplay(char newDisplay);
    void setCoords(int row, int column);
    void setEmpty(bool newEmpty);
    void setMoved(bool newIsMoved);

    // other methods
    virtual vector<ChessSquare> generatePath(ChessPiece &dest);
    virtual bool isValidMove(ChessPiece &dest); // check move validity (movement)
    int abs(int p); // returns the absolute value of path p (distance)
};

#endif
