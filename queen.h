#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Board;

class Queen: public Piece {
    public:
        Queen(Color color);
        bool validMove(Board &board, Coordinate start, Coordinate end) override;
        char getLetter() override;
};

#endif
