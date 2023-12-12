#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
class Board;

class Pawn: public Piece {

    bool en_passant = false; 
    bool firstMove = true; 
    bool promote = false; 

    bool castled = false;
    bool castlingLeft = false;
    bool castlingRight = false;
    
    public: 
        // Ctor 
        Pawn(Color color);
        bool validMove(Board& board, Coordinate start, Coordinate end)override; 
        char getLetter(); // returns the letter based on the piece and the colour for textdisplay

        Piece clone(PieceType piece);
        //bool captures (Coordinate start, Coordinate end);
        bool isEnpassant() override; 
        void setPass(bool val) override;
    
        bool canPromote() override; 
     
};

#endif
