#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  Font f;
  XFontStruct * font;
  XFontStruct * font_default;
  unsigned long colours[10];

 public:
  Xwindow(int width=1024, int height=800);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  void setUpFont(const std::string& fontname);

  void drawString(int x, int y, std::string msg, int colour, const std::string& fontName);
};


#endif
