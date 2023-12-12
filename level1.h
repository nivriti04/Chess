#ifndef __LEVEL1_H__
#define __LEVEL1_H__
#include "computer.h"
#include "player.h"

class Board;

class Level1: public Computer {
    
    public:
        Level1(Color color);
        void makeMove(Board &board) override;
}; 

#endif
