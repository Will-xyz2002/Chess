#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include "observer.h"
#include "chessPiece.h"


class TextDisplay: public Observer {
    char display[8][8];
    const int boardSize = 8;

public:
    TextDisplay();
    void notify(ChessPiece &piece) override;
    void displayTurn(ChessColour colour);
    void displayInvalidMove();
};

#endif
