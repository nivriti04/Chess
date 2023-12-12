#include "knight.h"
#include "board.h"

Knight::Knight(Color color) : Piece (color, PieceType::Knight) {}

bool validSquare(int startX, int startY, int endX, int endY){

     if(startX+2 == endX || startX-2 == endX){
        if(startY-1 == endY || startY+1 == endY){
            return true; 
        }
    } else if(startX+1 == endX || startX-1 == endX){
        if(startY-2 == endY || startY+2 == endY){
            return true; 
        }
    }
    return false; 
}


bool Knight::validMove(Board &board, Coordinate start, Coordinate end){

    // checking if the end co-ordinate is a valid square that the piece can move onto
    if(!validSquare(start.xPos, start.yPos, end.xPos, end.yPos)){
        return false; 
    }

    // if the end positon is a piece on the same team 
    if(board.getPiece(end.xPos, end.yPos).getColor() == color){
        return false; 
    } 

    // if (selfCheck (board, end)) {
    //     return false;
    // }

    return true; 
   
}

char Knight::getLetter(){

    if(color == Color::White){
        return 'N'; 
    } else{
        return 'n'; 
    }

}


