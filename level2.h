#ifndef __LEVEL2_H__
#define __LEVEL2_H__
#include "computer.h"
#include "piece.h"

class Board;

class Level2: public Computer{
    public:
        Level2 (Color team);
         void makeMove(Board &board);

}; 

#endif
