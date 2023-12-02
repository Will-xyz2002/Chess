#include "textDisplay.h"
TextDisplay::TextDisplay() { 
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if ((r + c)% 2 == 0) display[r][c] = ' ';
            else display[r][c] = '_';
        }
    }
}

void TextDisplay::setBoard(ChessBoard &board) {
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            display[r][c] = board.getPiece(r,c).getDisplay();
        }
    }
}

void TextDisplay::notify(ChessPiece &piece) {
    int row = piece.getCoords().getRow();
    int column = piece.getCoords().getColumn();
    display[row][column] = piece.getDisplay();
}

void TextDisplay::outputTurn(bool whiteTurn) {
    if (whiteTurn) cout << "White turn." << endl;
    else cout << "Black turn." << endl;
}

void TextDisplay::outputInvalidPiece() {
    cout << "Invalid piece. Please enter [a-h][1-8]" << endl;
}

void TextDisplay::outputInvalidRow() {
    cout << "Invalid row input - row needs to be from 1 to 8" << endl;
}

void TextDisplay::outputInvalidColumn() {
    cout << "Invalid column input - column needs to be a letter a to h" << endl;
}

void TextDisplay::outputInvalidMove() {
    cout << "Invalid move. Please try again." << endl;

}
void TextDisplay::outputCheckmate(bool whiteTurn) {
    cout << "Checkmate!";
    if (whiteTurn) cout << "Black wins!" << endl;
    else cout << "White wins!" << endl;
}

void TextDisplay::outputStalemate() {
    cout << "Stalemate!" << endl;
}

void TextDisplay::outputCheck(bool whiteTurn) {
    if (whiteTurn) cout << "White is in check." << endl;
    else cout << "Black is in check." << endl;
}

std::ostream &operator<<(std::ostream &out, TextDisplay t) {
    int column = 8;
    char row = 'a';
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        out << column << ' ';
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            out << t.display[r][c];
        }
        out << endl;
        column -= 1;
    }
    out << endl;
    out << ' ' << ' ';
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        out << row;
        row += 1;
    }
    out << endl;
    return out;
}
