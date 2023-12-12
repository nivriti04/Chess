#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
class Board;

class Rook: public Piece {
    public:
        Rook(Color color);
        bool validMove(Board &board, Coordinate start, Coordinate end) override;
        char getLetter();
};

#endif
