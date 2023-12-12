#ifndef __EMPTY_H__
#define __EMPTY_H__
#include "piece.h"
class Board;

class EmptyPiece: public Piece {
    public: 
        EmptyPiece(Color color);
        char getLetter();
        bool validMove (Board &board, Coordinate start, Coordinate end);
};

#endif
