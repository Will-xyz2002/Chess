#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include "observer.h"
#include "chessPiece.h"
#include "chessBoard.h"
#include <iostream>


class TextDisplay: public Observer {
    char display[8][8];
    const int boardSize = 8;

public:
    TextDisplay();
    void setBoard(ChessBoard &board);
    void notify(ChessPiece &piece) override;


    void outputTurn(bool whiteTurn);
    void outputInvalidPiece();
    void outputInvalidRow();
    void outputInvalidColumn();
    void outputInvalidMove();
    void outputCheckmate(bool whiteTurn);
    void outputStalemate();
    void outputCheck(bool whiteTurn);


    friend std::ostream &operator<<(std::ostream &out, TextDisplay t);
};

#endif
