#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "chessPiece.h"
#include "textDisplay.h"
#include <memory>
#include <string>


const int BOARD_DIMENSION = 8;

class ChessBoard {
    std::vector<std::vector<ChessPiece>> board;
    std::unique_ptr <King> whiteKing;
    std::unique_ptr <King> blackKing;
    std::unique_ptr<TextDisplay> t;
    bool isUnderAttack(ChessPiece &target, ChessPiece &piece);
    bool validMoveExist(ChessColour colour);


public:
    ChessBoard();
    ChessBoard(const ChessBoard &other);
    
    ChessPiece getPiece(int row, int column);

    void init();                                                   // initialize the chess board with standard chess pieces
    void addPiece(char pieceType, std::string position);           // add piece to the board
    void removePiece(std::string position);                        // remove piece from the board (if not Empty)
    bool kingIsUnderAttack(ChessColour colour);                    // return whether a white/black king is in check
    virtual void chessMove();                                      // make a move
    bool isValidBoard();                                           // return whether the setup board is valid
    void emptyBoard();                                             // make the board empty (all Empty pieces)
};
#endif
