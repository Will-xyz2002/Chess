#ifndef WINDOW_H
#define WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  XFontStruct *font;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  // height > width;
  int width = 560;
  int height = 760;

 public:
  Xwindow();  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, const char *msg, int length, int colour);

  // accessor
  int getWidth();
  int getHeight();
};

#endif
