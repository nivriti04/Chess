#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"
#include "board.h"

class Human: public Player{
    public: 
        Human(Color team); 
        void makeMove(Board &board) override; 

}; 

#endif
