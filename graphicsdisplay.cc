#include "graphicsdisplay.h"
#include "chessPiece.h"
#include "chessBoard.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow *xw, int gridSize)
    : xw(xw), gridSize(gridSize), display(gridSize, vector<char>(gridSize, '\0')),
    displayColour(gridSize, vector<ChessColour>(gridSize, ChessColour::Nocolour)) {
        drawGrid();
    }

void GraphicsDisplay::setBoard(ChessBoard &board) {
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            display[r][c] = board.getPiece(r,c).getDisplay();
            displayColour[r][c] = board.getPiece(r, c).getColour();
        }
    }
}

void GraphicsDisplay::notify(ChessPiece &piece) {
    int row = piece.getCoords().getRow();
    int col = piece.getCoords().getColumn();
    char piecedisplay = piece.getDisplay();
    display[row][col] = piecedisplay;
    ChessColour chessColour = piece.getColour();
    drawCell(row, col, piecedisplay, chessColour);
}

void GraphicsDisplay::drawCell(int r, int c, char piecedisplay, ChessColour chessColour) {
    int cellSize = 560 / gridSize;
    int x = c * cellSize;
    int y = r * cellSize;
    
    // Determine the colour of the cell
    // and the colour of the text for the piece
    int cellColour = ((r + c) % 2 == 0) ? Xwindow::White : Xwindow::Black;
    int textColour, highlightColour;
    // Set text and highlight colours based on chess piece colour
    if (chessColour == ChessColour::White) {
        textColour = Xwindow::White;
        highlightColour = Xwindow::Black; // Highlight for visibility
    } else if (chessColour == ChessColour::Black) {
        textColour = Xwindow::Black;
        highlightColour = Xwindow::White; // Highlight for visibility
    } else {
        highlightColour = cellColour; // No piece, no highlight
    }

    // Draw the cell with the colour
    xw->fillRectangle(x, y, cellSize, cellSize, cellColour);
    
    // If the cell is not empty, draw the piece character
    if (piecedisplay != '\0' && piecedisplay != '_') {
        int highlightSize = cellSize / 2; // Adjust size for highlight background
        int highlightSizeX = highlightSize / 1.7;
        int highlightPosX = highlightSizeX;
        int highlightSizeY = highlightSize / 1.2;
        int highlightPosY = highlightSizeY / 1.5;
        int highlightX = x + (cellSize - highlightPosX) / 2;
        int highlightY = y + (cellSize - highlightPosY) / 2;
        xw->fillRectangle(highlightX, highlightY, highlightSizeX, highlightSizeY, highlightColour);

        int textX = x + (cellSize / 2) - 5; // Adjust X position for centering
        int textY = y + (cellSize / 2) + 10; // Adjust Y position for centering
        xw->drawString(textX, textY, &piecedisplay, 1, textColour);
    }
}

void GraphicsDisplay::drawGrid() {
  for (int r = 0; r < BOARD_DIMENSION; ++r) {
    for (int c = 0; c < BOARD_DIMENSION; ++c) {
      drawCell(r, c, display[r][c], displayColour[r][c]);
    }
  }
}
