#include "chessPiece.h"

ChessPiece::ChessPiece(ChessColour colour, ChessSquare coords, bool empty)
    : colour{colour}, coordinate{coords}, empty{empty} {}

ChessPiece::~ChessPiece() {}

// copy ctor
ChessPiece(const ChessPiece &other)
    : colour{other.colour}, coordinate{other.coordinate}, empty{other.empty} {}

// move ctor
ChessPiece(ChessPiece &&other) {}



