#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
class Board;

class Bishop: public Piece {
    public: 
        Bishop(Color color);
        bool validMove(Board &board, Coordinate start, Coordinate end) override;
        char getLetter();
};

#endif
