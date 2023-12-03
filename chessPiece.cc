#include <vector>
#include "chessPiece.h"

using namespace std;

// default ctor
ChessPiece::ChessPiece(ChessType type, ChessColour colour, ChessSquare coords, bool empty)
    : type{type}, colour{colour}, coordinate{coords}, empty{empty} {}

// dtor
ChessPiece::~ChessPiece() {}

// copy ctor
ChessPiece::ChessPiece(const ChessPiece &other)
    : type{other.type}, colour{other.colour}, coordinate{other.coordinate}, display{other.display},
      isMoved{other.isMoved}, empty{other.empty} {}

// move ctor
ChessPiece::ChessPiece(ChessPiece &&other)
    : type{other.type}, colour{other.colour}, coordinate{move(other.coordinate)}, display{other.display},
      isMoved{other.isMoved}, empty{other.empty} {
    // Reset members of other
    other.type = ChessType::Empty;
    other.colour = ChessColour::Nocolour;
    other.display = '\0';
    other.isMoved = false;
    other.empty = true;
}

// copy assignment operator
ChessPiece &ChessPiece::operator=(const ChessPiece &other) {
    if (this != &other) {
        // Copy all members
        type = other.type;
        colour = other.colour;
        coordinate = other.coordinate;
        display = other.display;
        isMoved = other.isMoved;
        empty = other.empty;
    }
    return *this;
}

// move assignment operator
ChessPiece &ChessPiece::operator=(ChessPiece &&other) {
    if (this != &other) {
        // Move all members
        type = other.type;
        colour = other.colour;
        coordinate = move(other.coordinate);
        display = other.display;
        isMoved = other.isMoved;
        empty = other.empty;

        // Reset members of other
        other.type = ChessType::Empty;
        other.colour = ChessColour::Nocolour;
        other.display = '\0'; // Default char
        other.isMoved = false;
        other.empty = true;
    }
    return *this;
}

// accessors
ChessColour ChessPiece::getColour() { return colour; }
ChessSquare ChessPiece::getCoords() { return coordinate; }
ChessType ChessPiece::getType() { return type; }
char ChessPiece::getDisplay() { return display; }
bool ChessPiece::isEmpty() { return empty; }
bool ChessPiece::hasMoved() { return isMoved; }

// settors
void ChessPiece::setColour(ChessColour newColour) { colour = newColour; }
void ChessPiece::setDisplay(char newDisplay) { display = newDisplay; }
void ChessPiece::setCoords(int row, int column) { coordinate.setCoords(row, column); }
void ChessPiece::setEmpty(bool newEmpty) { this->empty = newEmpty; }
void ChessPiece::setMoved(bool newIsMoved) { this->isMoved = newIsMoved; }

// other methods
vector<ChessSquare> ChessPiece::generatePath(ChessPiece &dest) {
    return vector<ChessSquare>();
}
bool ChessPiece::isValidMove(ChessPiece &dest) { return false; }
int ChessPiece::abs(int p) { return (p >= 0) ? p : -p; }

