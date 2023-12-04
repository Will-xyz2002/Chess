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
  int labelOffset;

 public:
  GraphicsDisplay(Xwindow *xw, int gridSize);
  ~GraphicsDisplay();
  void setBoard(ChessBoard &board);
  void notify(ChessPiece &piece) override;

  // Additional methods to draw the grid
  void drawTitle();
  void drawCell(int r, int c, char piecedisplay, ChessColour chessColour);
  void drawGrid();
};

#endif
