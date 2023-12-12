#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>
#include "subject.h"
using namespace std;

class Board;
enum class Color;
enum class PieceType;

class Piece {
    public:
        struct Coordinate {
            int xPos;
            int yPos;
        };

   
    protected:
        Color color;
        PieceType pieceType;
        vector<Coordinate> allValidMoves;
        int numValidMoves = 0;
        bool move = false;
        bool canBeCaptured = false;
        
        bool castled = false;
        bool castlingLeft = false;
        bool castlingRight = false;

    public:
        Coordinate curCoords;
        string name;
        bool enpassed = false;
        Piece();
        virtual ~Piece(); 
        Piece(Color &color, PieceType pieceType);
        PieceType getPieceType () const;
        void setPieceType(PieceType pt); 
        Color getColor () const;
        virtual bool isEnpassant();
        virtual bool canPromote(); 
        virtual void setPass(bool val); 
        virtual char getLetter() ;
        virtual bool validMove (Board &board, Coordinate start, Coordinate end);
        bool hasMoved () const;
        void setMoved(bool mv);

        bool hasCastled();
        void setCastled();

        bool getIsCastlingLeft();
        void setIsCastlingLeft(bool val);
        
        bool getIsCastlingRight();
        void setIsCastlingRight(bool val);

        bool isEnpassanting(Board& board, Coordinate end);

        void setCapture(bool val); 
        bool getCapture(); 

        void setCoordinates(int x, int y);

        bool selfCheck(Board& board, Coordinate end);


        void updateValidMoves(Board& board);

        //implement starting coordinates here
        Coordinate getCoordinates();

        //function to get the number of coordinates it can move to
        int getValidMoveCount();
        //returns the coordinate at the index
        Coordinate getValidMove(int index);

        void remove (Coordinate end);
    
};

#endif
