#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include "iostream"
#include <vector>
#include <memory>

class Board; 
const int boardSize = 8; 

using namespace std; 

class TextDisplay: public Observer {

     vector<vector<char>> theDisplay;

 public:
    // Ctor  
    TextDisplay();

    // Updates the grid to move the pieces 
    void notify(Board &board);

    //Dtor 
    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
