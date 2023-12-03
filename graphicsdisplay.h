#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <vector>
#include "observer.h"
#include "chessPiece.h"
#include "chessBoard.h"
#include "window.h"

using namespace std;

class GraphicsDisplay: public Observer {
  Xwindow *xw;
  int gridSize;
  vector<vector<char>> display;
  vector<vector<ChessColour>> displayColour;

 public:
  GraphicsDisplay(Xwindow *xw, int gridSize);
  void setBoard(ChessBoard &board);
  void notify(ChessPiece &piece) override;

  // Additional methods to draw the grid
  void drawCell(int r, int c, char piecedisplay, ChessColour chessColour);
  void drawGrid();
};

#endif
