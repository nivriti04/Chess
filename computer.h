#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player{
    
    public: 
        Computer(Color team) : Player {team} {}
        virtual ~Computer() = default; 
}; 

#endif
