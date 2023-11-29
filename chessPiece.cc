#include <vector>
#include "chessPiece.h"

using namespace std;

ChessPiece::ChessPiece(ChessColour colour, ChessSquare coords, bool empty)
    : colour{colour}, coordinate{coords}, empty{empty} {}

ChessPiece::~ChessPiece() {}

// copy ctor
ChessPiece::ChessPiece(const ChessPiece &other)
    : colour(other.colour), coordinate(other.coordinate), display(other.display),
      isMoved(other.isMoved), empty(other.empty), observers(other.observers) {
    // deep copy?
}

// move ctor
ChessPiece::ChessPiece(ChessPiece &&other)
    : colour(other.colour), coordinate(move(other.coordinate)), display(other.display),
      isMoved(other.isMoved), empty(other.empty), observers(move(other.observers)) {
    // Reset the members of 'other' ?
}


ChessPiece &ChessPiece::operator=(const ChessPiece &other) {
    if (this != &other) {
        // Copy all members
        colour = other.colour;
        coordinate = other.coordinate;
        display = other.display;
        isMoved = other.isMoved;
        empty = other.empty;
        observers = other.observers;
        // Deep copy ?
    }
    return *this;
}

ChessPiece &ChessPiece::operator=(ChessPiece &&other) {
    if (this != &other) {
        // Move all members
        colour = other.colour;
        coordinate = move(other.coordinate);
        display = other.display;
        isMoved = other.isMoved;
        empty = other.empty;
        observers = move(other.observers);

        // Reset the members of 'other' ?
    }
    return *this;
}

// accessors
ChessColour getColour() { return colour; }
ChessSquare getCoords() { return coordinate; }
char getDisplay() { return display; }
bool isEmpty() { return empty; }
bool hasMoved() { /* fill in */ }

// settors
void setColour(ChessColour colour) { colour = colour; }
void setCoords(int row, int column) {
    coordinate.row = row;
    coordinate.column = column;
}
void setEmpty(bool empty) { empty = empty; }
void setMoved(bool isMoved) { isMoved = isMoved; }

int abs(int p) {
    if(p >= 0) return p;
    else return -p;
}
