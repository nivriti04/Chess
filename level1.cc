#include "level1.h"
#include "board.h"
#include <cstdlib>  
#include <ctime> 


Level1::Level1(Color team): Computer{team} {}

void Level1::makeMove(Board &board) {

    vector<Board::Moves> allValidMoves = board.getAllMoves(team);
   
    int moveCount = allValidMoves.size(); 

    if(moveCount > 0){
        srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % moveCount;

        Board::Moves finalMove = allValidMoves[randomIndex]; 
      
        board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
        board.notifyObservers(board); 

    }
}
