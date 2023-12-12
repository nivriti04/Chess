#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
class Board;

class King: public Piece {
    public: 
        King(Color color);
        bool validMove(Board &board, Coordinate start, Coordinate end);
        char getLetter();
      
};

#endif
