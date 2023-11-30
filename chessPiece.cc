#include <vector>
#include "chessPiece.h"

using namespace std;

ChessPiece::ChessPiece(ChessType type, ChessColour colour, ChessSquare coords, bool empty): 
                        type{type}, colour{colour}, coordinate{coords}, empty{empty} {}

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
ChessColour ChessPiece::getColour() { return colour; }
ChessSquare ChessPiece::getCoords() { return coordinate; }
char ChessPiece::getDisplay() { return display; }
bool ChessPiece::isEmpty() { return empty; }
bool ChessPiece::hasMoved() { return isMoved; }

// settors
void ChessPiece::setColour(ChessColour colour) { colour = colour; }
void ChessPiece::setCoords(int row, int column) {
    coordinate.setCoords(row, column);
}


void ChessPiece::setEmpty(bool empty) { this->empty = empty; }
void ChessPiece::setMoved(bool isMoved) { this->isMoved = isMoved; }

int abs(int p) {
    if(p >= 0) return p;
    else return -p;
}

void ChessPiece::attach(Observer &o) {
    observers.emplace_back(o);
}

