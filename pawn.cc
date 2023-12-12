#include "pawn.h"
#include "board.h"

Pawn::Pawn(Color color): Piece (color, PieceType::Pawn) {
    en_passant = false; 
    firstMove = true; 
}

bool Pawn::isEnpassant(){
    return en_passant; 
}

void Pawn::setPass(bool val){
    en_passant = val; 
}

bool Pawn::canPromote(){
    return promote; 
}

bool Pawn::validMove(Board &board, Coordinate start, Coordinate end) {

    if ((start.xPos == end.xPos) && (start.yPos == end.yPos)) {return false;} 

    if(color == Color::White){
      
        // First Move and Move 2 spaces
        if(end.xPos == start.xPos-2 && start.xPos == 6 && end.yPos == start.yPos){  
            if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty &&
                board.getPiece(end.xPos+1, end.yPos).getPieceType() == PieceType::Empty ){ // both squares empty 
                    
                    if(board.getPiece(end.xPos, (end.yPos == 0) ? 1 : end.yPos-1).getPieceType() == PieceType::Pawn || // if you could be attacked by a pawn
                        board.getPiece(end.xPos, (end.yPos == 7) ? 6 : end.yPos+1).getPieceType() == PieceType::Pawn){ // when you move one space 
                           board.getPiece(start.xPos - 1, start.yPos).enpassed = true;  // set pawn infront of
                    }
                    firstMove = false; 
                    return true;
                }
        } 
        
        if ((end.xPos == start.xPos-1 && board.getPiece(end.xPos, end.yPos).enpassed == true &&
            board.getPiece(end.xPos, start.yPos + 1).getPieceType() == PieceType::Empty) &&
            (abs(end.yPos - start.yPos) == 1)) {
            return true;
        }

        // Movng Up 
        else if(end.xPos == start.xPos-1){
            en_passant = false; 
            if(end.yPos == start.yPos-1){ // Left Diagnoal 
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty || 
                    board.getPiece(end.xPos, end.yPos).getColor() == color){  // Empty or Same colour 
                        return false; 
                } else{
                    return true; 
                }
            } else if(end.yPos == start.yPos+1){ //Right Diagonal
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty || 
                    board.getPiece(end.xPos, end.yPos).getColor() == color){  // Empty or Same colour 
                        return false; 
                } else{
                    return true; 
                }

            } else if (end.yPos == start.yPos){ // Normal Move 
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty){ // Spot Empty 
                    if(end.xPos == 0){
                        promote = true; 
                    }
                    return true; 
                }
            }
            
        } else if(end.yPos == start.yPos-1 || end.yPos == start.yPos+1){ // Move Left or Right 
            if(board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Pawn && // If a pawn that you can enPass 
            board.getPiece(end.xPos, end.yPos).isEnpassant()){
                return true;  
            }
        }  
    

    } else if (color == Color::Black) { // BLACK  
        
        // First Move and Move 2 spaces
        if(end.xPos == start.xPos+2 && start.xPos == 1 && end.yPos == start.yPos){  
            if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty &&
                board.getPiece(end.xPos-1, end.yPos).getPieceType() == PieceType::Empty ){ // both squares empty 
                    
                    if(board.getPiece(end.xPos, (end.yPos == 0) ? 1 : end.yPos-1).getPieceType() == PieceType::Pawn || // if you could be attacked by a pawn
                        board.getPiece(end.xPos, (end.yPos == 7) ? 6 : end.yPos+1).getPieceType() == PieceType::Pawn){ // when you move one space                            
                            board.getPiece(start.xPos + 1, start.yPos).enpassed = true;                      
                    }
                    firstMove = false; 
                    return true;
                }// return false 
        } 

        if ((end.yPos == start.yPos+1 && board.getPiece(end.xPos, end.yPos).enpassed == true &&
            board.getPiece(end.xPos, start.yPos + 1).getPieceType() == PieceType::Empty) &&
            (abs(end.yPos - start.yPos) == 1)) {
            return true;
        }

        // Moving ahead 
        else if(end.xPos == start.xPos+1){
            en_passant = false; 
            if(end.yPos == start.yPos-1){ // Left Diagnoal 
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty || 
                    board.getPiece(end.xPos, end.yPos).getColor() == color){  // Empty or Same colour 
                        return false; 
                } else{
                    return true; 
                }
            } else if(end.yPos == start.yPos+1){ //Right Diagonal
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty || 
                    board.getPiece(end.xPos, end.yPos).getColor() == color){  // Empty or Same colour 

                        return false; 
                } else{
                    return true; 
                }

            } else if (end.yPos == start.yPos){ // Normal Move 
                if (board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty){ // Spot Empty 
                    if(end.xPos == 7){
                        promote = true; 
                    }
                    return true; 
                }
            }
        }else if((end.yPos == start.yPos-1 || end.yPos == start.yPos+1) && start.xPos == end.xPos){ // Move Left or Right 
            if(board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Pawn && // If a pawn that you can enPass 
                board.getPiece(end.xPos, end.yPos).isEnpassant()){
                return true; 
            }
        }  
        
    }  
    
    return false;
}

char Pawn::getLetter(){

    if(color == Color::White){
        return 'P'; 
    } else{
        return 'p'; 
    }
}


