#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "chessPiece.h"
#include "chessMove.h"
#include "observer.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "empty.h"
#include <memory>
#include <string>


const int BOARD_DIMENSION = 8;
ChessSquare convertPosition(string position);

class ChessBoard {
    std::vector<std::vector<ChessPiece>> board;
    ChessPiece *whiteKing = nullptr;
    ChessPiece *blackKing = nullptr;
    std::vector<Observer*> observers;

    bool isUnderAttack(ChessSquare &target, ChessSquare &piece);
    bool validMoveExist(ChessSquare piece);

public:
    ChessBoard();
    ChessBoard(const ChessBoard &other);
    
    ChessPiece getPiece(int row, int column);
    
    void init();                                                                        // initialize the chess board with standard chess pieces
    void addPiece(char pieceType, std::string position);                                // add piece to the board
    void addPiece(ChessPiece &piece);                                                   // add piece to the board (using piece instead of input)
    void removePiece(std::string position);                                             // remove piece from the board (if not Empty)
    bool kingIsUnderAttack(ChessColour colour);                                         // return whether a white/black king is in check
    bool isValidMove(ChessSquare &initial, ChessSquare &dest, ChessColour turn);        // determine whether a move is valid (movement)
    bool isValidPath(ChessSquare &initial, ChessSquare &dest);                          // determine whether a move is valid (no obstacle)
    bool isCastlingPossible(ChessSquare &initial, ChessSquare &dest, ChessColour turn); // check whether the castling move can be achieved
    bool isEnPassantPossible(ChessSquare &initial, ChessSquare &dest, ChessColour turn, 
                             ChessMove &lastMove);                                      // check whether the en passant move can be achieved
    void chessMove(ChessSquare initial, ChessSquare dest);                              // make a standard move
    // void chessMoveCastling(ChessSquare king, ChessSquare rook);                      // make a castling move
    bool isValidBoard();                                                                // return whether the setup board is valid
    void emptyBoard();                                                                  // make the board empty (all Empty pieces)
    bool validMoveExist(ChessColour colour);                                            // return true whenever there are any 
                                                                                        // existing move available in colour side
    
    void pawnPromotion(int row, int column, ChessColour colour);                        // promote pawn
    bool pawnCapturingMove(ChessSquare &initial, ChessSquare &dest);
    void attach(Observer *o);
    void notifyObservers(ChessPiece &piece);
    vector<ChessMove> PossibleMoveGenerator(ChessColour colour); // return a vector of chessmove which are all possible moves of the given colour
    friend std::ostream &operator<<(ostream &out, ChessBoard &b);
};
#endif
