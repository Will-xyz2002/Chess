#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "chessPiece.h"
#include "observer.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "empty.h"
#include "textDisplay.h"
#include <memory>
#include <string>


const int BOARD_DIMENSION = 8;
ChessSquare convertPosition(string position);

class ChessBoard {
    std::vector<std::vector<ChessPiece>> board;
    std::unique_ptr <King> whiteKing = nullptr;
    std::unique_ptr <King> blackKing = nullptr;
    std::vector<Observer*> observers;

    bool isUnderAttack(ChessPiece &target, ChessPiece &piece);
    bool validMoveExist(ChessPiece &piece);

public:
    ChessBoard();
    ChessBoard(const ChessBoard &other);
    
    ChessPiece getPiece(int row, int column);
    
    void init();                                                                // initialize the chess board with standard chess pieces
    void addPiece(char pieceType, std::string position);                        // add piece to the board
    void addPiece(ChessPiece &piece);                                           // add piece to the board (using piece instead of input)
    void removePiece(std::string position);                                     // remove piece from the board (if not Empty)
    bool kingIsUnderAttack(ChessColour colour);                                 // return whether a white/black king is in check
    bool isValidMove(ChessPiece &initial, ChessPiece &dest, ChessColour turn);  // determine whether a move is valid (movement)
    bool isValidPath(ChessPiece &initial, ChessPiece &dest);                    // determine whether a move is valid (no obstacle)
    void chessMove(ChessSquare initial, ChessSquare dest);                      // make a move
    bool isValidBoard();                                                        // return whether the setup board is valid
    void emptyBoard();                                                          // make the board empty (all Empty pieces)
    bool validMoveExist(ChessColour colour);                                    // return true whenever there are any 
                                                                                // existing move available in colour side

    
    void attach(Observer &o);
    void notifyObservers(ChessPiece &p);
};

#endif
