#include "human.h"
#include "piece.h"
#include "board.h"
#include <iostream>
#include <string>
#include "subject.h"
#include <sstream>


Human::Human(Color team): Player{team} {}

Piece::Coordinate convertStringToCoords(string s) {
    // ex. a8 -> 0 0  
    int x =  '8' - s[1];
    int y =  s[0] - 'a'; 
   
    return Piece::Coordinate{x,y};
}

void Human::makeMove(Board &board) {

    std::string startString, endString, updatedPawn;
    std::cin >> startString >> endString;

    Piece::Coordinate start = convertStringToCoords(startString);
    Piece::Coordinate end = convertStringToCoords(endString);

    // Check if starting square is empty
    if (board.getPiece(start.xPos, start.yPos).getPieceType() == PieceType::Empty) {
        throw invalid_argument("No piece to move");
    }

    if (board.getPiece(start.xPos, start.yPos).getColor() != team) {
        throw invalid_argument("Not your piece");
    }

    Piece& piece = board.getPiece(start.xPos, start.yPos);

    // calls valid move of that piece
    bool can_move = piece.validMove(board, start, end);
    
    if(can_move){
        if(piece.selfCheck(board, end)){
            can_move = !can_move; 
        }
    }

    if (!can_move) {
        throw invalid_argument("Move not possible");
    } else if(board.getPiece(start.xPos, start.yPos).canPromote()){
            
            board.updatePiece(start.xPos, start.yPos, end.xPos, end.yPos); 
            board.notifyObservers(board); 
            cout << "What would you like to promote to:" << endl;
            std::cin >> updatedPawn; 
            PieceType newType; 

            if(updatedPawn == "Q"){
                newType = PieceType::Queen; 
            } else if(updatedPawn == "R"){
                newType = PieceType::Rook;
            }else if(updatedPawn == "B"){
                newType = PieceType::Bishop;
            } else if(updatedPawn == "N"){
                newType = PieceType::Knight;
            } else{
                throw invalid_argument("Not valid promotion");
            }

            board.setPiece(end.xPos, end.yPos, newType, team);
            board.notifyObservers(board);

        } else {
            if ((board.getPiece(start.xPos, start.yPos).hasCastled() == false) &&
               ((board.getPiece(start.xPos, start.yPos).getIsCastlingLeft() == true))) {
                    board.getPiece(start.xPos, start.yPos).setCastled();

                    board.updatePiece(start.xPos, 0, end.xPos, 3); 
                    board.notifyObservers(board); 
                    board.getPiece(start.xPos, 3).setMoved(true);
                    board.getPiece(end.xPos, end.yPos).setCoordinates(end.xPos, end.yPos);

            } else if ((board.getPiece(start.xPos, start.yPos).hasCastled() == false) &&
               ((board.getPiece(start.xPos, start.yPos).getIsCastlingRight() == true))) {
                    
                    board.getPiece(start.xPos, start.yPos).setCastled();

                    board.updatePiece(start.xPos, 7, end.xPos, 5); 
                     board.notifyObservers(board); 
                    board.getPiece(start.xPos, 5).setMoved(true);
                    board.getPiece(end.xPos, end.yPos).setCoordinates(end.xPos, end.yPos);
            } 

            bool plswork = board.getPiece(start.xPos, start.yPos).getPieceType() == PieceType::Pawn && 
                        board.getPiece(start.xPos, start.yPos).isEnpassanting(board,end);

            if(plswork) {
                board.setPiece((board.getPiece(start.xPos, start.yPos).getColor() == Color::White) ? 3 : 5, end.yPos, 
                                PieceType::Empty, Color::EmptyCol);
            } 
            board.updatePiece(start.xPos, start.yPos, end.xPos, end.yPos); 
            board.notifyObservers(board); 
            board.getPiece(end.xPos, end.yPos).setMoved(true);
            board.getPiece(end.xPos, end.yPos).setCoordinates(end.xPos, end.yPos);
        


            
        }   
        
       
        
    }
    
