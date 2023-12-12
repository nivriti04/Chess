#ifndef __LEVEL3_H__
#define __LEVEL3_H__
#include "computer.h"

class Board;

class Level3: public Computer{
    public:
        Level3 (Color team);
        void makeMove(Board &board);
}; 

#endif
