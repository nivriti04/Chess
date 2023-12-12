#include "level2.h"
#include "level1.h"
#include "board.h"
#include <cstdlib>  
#include <ctime>  


Level2::Level2(Color team): Computer{team} {}

void Level2::makeMove(Board &board) {

    Level1 l1(team); 

    int captureCount = 0;  // # of capturing moves 

    vector<Board::Moves> allValidMoves = board.getAllMoves(team); 

    vector<Board::Moves> attackMoves; 

    for (const auto move : allValidMoves) {
        if(move.capture){
            attackMoves.emplace_back(move); 
            captureCount++; 
        }
    }


    if(captureCount > 0){
      srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % captureCount;
        Board::Moves finalMove = attackMoves[randomIndex]; 

        board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
        board.notifyObservers(board); 
        if(board.getPiece(finalMove.start.xPos, finalMove.end.yPos).canPromote()){

            board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
            board.setPiece(finalMove.start.xPos, finalMove.end.yPos, PieceType::Queen, team);
        }else{
            board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
            board.notifyObservers(board); 
        }


    } else{
        l1.makeMove(board); 
    }
   

}
