#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "chessSquare.h"
#include "observer.h"
#include <vector>

enum class ChessColour {White, Black, None};

class ChessPiece {
    ChessColour colour;
    ChessSquare coordinate;
    char display;
    bool isMoved = false;
    std::vector<Observer*> observers;
    virtual std::vector<ChessSquare> generatePath(ChessPiece &dest);


public:
    ChessPiece(ChessColour colour, ChessSquare coords);
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
    virtual bool isValidMove(ChessPiece &dest); // check move validity (movement)
    virtual bool isPathClear(ChessPiece &dest); // check move validity (no obstacle)
    void attach(Observer *o); // add observers
};
#endif
