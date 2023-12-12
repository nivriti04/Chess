#include "level3.h"
#include "level2.h"
#include "board.h"
#include <cstdlib>  
#include <ctime>  


Level3::Level3(Color team): Computer{team} {}

void Level3::makeMove(Board &board) {

    Level2 l2(team); 

    // getting all valid moves of the opponent team since the 
    // helper function can then set our teams pieces boolean for
    // capturing to be true 
    Color otherTeam = (team == Color::White) ? Color::Black : Color::White;

    // sees if the other team can attack any of ours 
    vector<Board::Moves> allValidMoves = board.getAllMoves(otherTeam);

    vector<Board::Moves> piecesUnderAttack; 

    int attackCount = 0; 

    for (const auto move : allValidMoves) {

        if(board.getPiece(move.start.xPos, move.start.yPos).getCapture()){
            piecesUnderAttack.emplace_back(move); 
            attackCount++; 
        }
    }

    if(piecesUnderAttack.size() > 0){

        srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % attackCount;
        Board::Moves finalMove = piecesUnderAttack[randomIndex]; 

        if(board.getPiece(finalMove.start.xPos, finalMove.end.yPos).canPromote()){

            board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
            board.setPiece(finalMove.start.xPos, finalMove.end.yPos, PieceType::Queen, team);
        }else{
            board.updatePiece(finalMove.start.xPos, finalMove.start.yPos, finalMove.end.xPos, finalMove.end.yPos); 
            board.notifyObservers(board); 
        }

    } else{
        l2.makeMove(board); 
    }
   

}
