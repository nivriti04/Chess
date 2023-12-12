#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include "piece.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

using namespace std; 

enum class Color {White = 0, Black, EmptyCol};  

// All types of pieces
enum class PieceType {King = 0, Knight, Queen, Bishop, Rook, Pawn, Empty}; 


class Board : public Subject {

    unique_ptr<Piece> pieces[8][8]; //contains 64 types of pieces
    
    bool graphicsOn = false;

    unique_ptr<TextDisplay> td = nullptr;
    // TextDisplay* td = nullptr; 

    unique_ptr<GraphicsDisplay> gd = nullptr;
    // GraphicsDisplay* gd = nullptr; 
    Xwindow xw;

    void setObservers(); 
    public:

        struct Moves{
            bool capture = false; 
            Piece::Coordinate start{}; 
            Piece::Coordinate end{}; 
        }; 

        vector<Moves> getAllMoves(Color team); 

        const int size = 8;

        //Big 5:
        Board(); 
        ~Board();

        void setGraphics(bool tval);

        // returns the opposite or enemy color of that provided
        Color getOpponentColor(Color color);

        //check and checkmate
        Piece::Coordinate getKingLocation(Color kingColor) const;

        // 
        void updatePiece(int oldX, int oldY, int newX, int newY); 
        
        // checks if the king of the given color is in check
        bool isKingInCheck(Color kingColor);

        // checks if the king of the given color has been mated
        bool isCheckmate(Color kingColor);
        
        // checks if the board is in a stalemate
        bool isStalemate(Color turnPlayerColor);
        void switchPieces(int oldX, int oldY, int endX, int endY, Color col, PieceType pt, bool mv, bool enp);
        // gets the current piece at a specific x and y coordinates
        Piece& getPiece(int x, int y) const;

        //will set piece at x and y to piece
        void setPiece (int x, int y, PieceType piece, Color color); 

        //checks if board is a valid setup
        bool isValidSetup ();

        // sets board to basic default mode
        void basicSetup();

        // set board to empty mode
        void emptySetup();

        // set the display type
        void setDisplayType (int display); 

        // output board        
        friend std::ostream &operator<<(std::ostream &out, const Board &b);

        void updateAllPieceValidMoves();

}; 

#endif
