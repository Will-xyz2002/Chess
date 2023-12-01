#include "chessMove.h"

ChessMove::ChessMove(ChessPiece &initial, ChessPiece &dest): initial{initial}, dest{dest} { }
ChessPiece ChessMove::getInitial() { return initial; }
ChessPiece ChessMove::getDest() { return dest; }
