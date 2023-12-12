#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include "observer.h"
#include "window.h"

class Board;

class GraphicsDisplay: public Observer {
  
  Xwindow &xw; 

  public:
    // Ctor 
    GraphicsDisplay(Xwindow &xw);

    // Updates the dispaly to move the pieces
    void notify(Board &board);
    
    void reset(); 

    // Dtor 
    ~GraphicsDisplay();
};

#endif
