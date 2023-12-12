#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "piece.h"

class Piece;
class Board;
enum class Color;

class Player {
    public: 
    Color team; 
    double score = 0; 

    Player(Color team); 
    Player();
    virtual ~Player(); 
    virtual void makeMove(Board &board) = 0;

    public:
}; 

#endif 
