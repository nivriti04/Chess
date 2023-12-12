#ifndef __MOVE_H__
#define __MOVE_H__
#include <string>
#include "board.h"
using namespace std;

enum moveType {Normal, Promotion, Enpass, Castling, PawnFirst};

class Move {
    
    int moveNumber;
    string moveNotation;
    PieceType piece_moved;
    int lastX;
    int lastY;
    int newX;
    int newY;
    moveType mt;
    PieceType promotedType;
    bool isCaptured;

};
#endif
