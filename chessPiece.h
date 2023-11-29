#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <vector>
#include "chessSquare.h"
#include "observer.h"

using namespace std;

enum class ChessColour {White, Black, None};

class ChessPiece {
    ChessColour colour;
    ChessSquare coordinate;
    char display;
    bool isMoved = false;
    bool empty;
    vector<Observer*> observers;

public:
    ChessPiece(ChessColour colour, ChessSquare coords, bool empty);
    ~ChessPiece();
    ChessPiece(const ChessPiece &other);
    ChessPiece(ChessPiece &&other);
    ChessPiece &operator=(const ChessPiece &other);
    ChessPiece &operator=(ChessPiece &&other);

    // accessors
    ChessColour getColour();
    ChessSquare getCoords();
    char getDisplay();
    bool isEmpty();
    bool hasMoved();

    // settors
    void setColour(ChessColour colour);
    void setCoords(int row, int column);
    void setEmpty(bool empty);
    void setMoved(bool isMoved);

    // other methods
    virtual vector<ChessSquare> generatePath(ChessPiece &dest);
    virtual bool isValidMove(ChessPiece &dest); // check move validity (movement)
    int abs(int p); // returns the absolute value of path p (distance)
    void attach(Observer *o); // add observers
};

#endif
