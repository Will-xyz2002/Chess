#include "graphicsdisplay.h"
#include "chessPiece.h"
#include "chessBoard.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize)
    : xw(make_unique<Xwindow>()), gridSize(gridSize), display(gridSize, vector<char>(gridSize, '\0')),
    displayColour(gridSize, vector<ChessColour>(gridSize, ChessColour::Nocolour)), labelOffset(24) {
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

void GraphicsDisplay::drawTitle() {
    // ASCII retrieved from https://patorjk.com/software/taag/#p=display&f=3-D&t=CHESS
    if(xw->getHeight() - xw->getWidth() >= 220) {
        const char* boundary = "===================================================";
        const char* slice1 = "   ******  **      ** ********  ********  ********";
        const char* slice2 = "  **////**/**     /**/**/////  **//////  **////// ";
        const char* slice3 = " **    // /**     /**/**      /**       /**       ";
        const char* slice4 = "/**       /**********/******* /*********/*********";
        const char* slice5 = "/**       /**//////**/**////  ////////**////////**";
        const char* slice6 = "//**    **/**     /**/**             /**       /**";
        const char* slice7 = " //****** /**     /**/******** ********  ******** ";
        const char* slice8 = "  //////  //      // //////// ////////  ////////  ";
        const char* command1 = "Commands: (g)ame ((h)uman or (c)omputer[1-4])";
        const char* command2 = "          (m)ove [a-h][1-8] [a-h][1-8] (Q,R,B,N)";
        const char* command3 = "          (r)esign (s)etup (+) (-) (=) (d)one";
        const char* command4 = "          (reset) (score)";
        int length = 50;
        
        xw->drawString(28, 20, boundary, length, Xwindow::White);
        xw->drawString(28, 40, slice1, length, Xwindow::White);
        xw->drawString(28, 50, slice2, length, Xwindow::White);
        xw->drawString(28, 60, slice3, length, Xwindow::White);
        xw->drawString(28, 70, slice4, length, Xwindow::White);
        xw->drawString(28, 80, slice5, length, Xwindow::White);
        xw->drawString(28, 90, slice6, length, Xwindow::White);
        xw->drawString(28, 100, slice7, length, Xwindow::White);
        xw->drawString(28, 110, slice8, length, Xwindow::White);
        xw->drawString(28, 130, boundary, length, Xwindow::White);
        xw->drawString(28, 150, command1, 45, Xwindow::White);
        xw->drawString(28, 170, command2, 48, Xwindow::White);
        xw->drawString(28, 190, command3, 45, Xwindow::White);
        xw->drawString(28, 210, command4, 25, Xwindow::White);
    }
}

void GraphicsDisplay::drawCell(int r, int c, char piecedisplay, ChessColour chessColour) {
    int cellSize = (xw->getWidth() - labelOffset) / gridSize;
    int down = xw->getHeight() - xw->getWidth();
    int x = labelOffset + c * cellSize;
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
    xw->fillRectangle(x, y + down, cellSize, cellSize, cellColour);
    
    // If the cell is not empty, draw the piece character
    if (piecedisplay != ' ' && piecedisplay != '_') {
        int highlightSize = cellSize / 2; // Adjust size for highlight background
        int highlightSizeX = highlightSize / 1.7;
        int highlightPosX = highlightSizeX;
        int highlightSizeY = highlightSize / 1.2;
        int highlightPosY = highlightSizeY / 1.5;
        int highlightX = x + (cellSize - highlightPosX) / 2;
        int highlightY = y + (cellSize - highlightPosY) / 2;
        xw->fillRectangle(highlightX, highlightY + down, highlightSizeX, highlightSizeY, highlightColour);

        int textX = x + (cellSize / 2) - 5; // Adjust X position for centering
        int textY = y + (cellSize / 2) + 10; // Adjust Y position for centering
        xw->drawString(textX, textY + down, &piecedisplay, 1, textColour);
    }
}

void GraphicsDisplay::drawGrid() {
  int cellSize = (560 - labelOffset) / gridSize;
  int down = xw->getHeight() - xw->getWidth();
  int baseX = labelOffset - 17; // Starting X position for the grid
  int baseY = labelOffset - 14; // Starting Y position for the grid
  
  drawTitle();

  for (int r = 0; r < BOARD_DIMENSION; ++r) {
    for (int c = 0; c < BOARD_DIMENSION; ++c) {
      drawCell(r, c, display[r][c], displayColour[r][c]);
    }
  }

  // Draw row labels (1, 2, 3, ... 8)
  for (int r = 0; r < BOARD_DIMENSION; ++r) {
    string label = to_string(BOARD_DIMENSION - r); // Rows are labeled from 8 to 1
    xw->drawString(baseX, down + baseY + r * cellSize + cellSize / 2, label.c_str(), label.length(), Xwindow::White);
  }

  // Draw column labels (a, b, c, ... h)
  // Adjust the Y position to be below the grid
  baseX += 11;
  int bottom = labelOffset + BOARD_DIMENSION * cellSize;
  bottom -= 6;
  for (int c = 0; c < BOARD_DIMENSION; ++c) {
    char label = 'a' + c;
    xw->drawString(baseX + c * cellSize + cellSize / 2 , down + bottom, &label, 1, Xwindow::White);
  }
}
