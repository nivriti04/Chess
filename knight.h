#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
class Board;

class Knight: public Piece {
    public: 
        Knight(Color color);
        bool validMove(Board &board, Coordinate start, Coordinate end) override;
        char getLetter(); 
};

#endif
