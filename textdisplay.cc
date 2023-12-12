#include "textdisplay.h"
#include "piece.h"
#include "board.h"


TextDisplay::TextDisplay() {

    theDisplay.resize(boardSize, vector<char>(boardSize));

    std::string firstRow = "rnbqkbnr";
    std::string lastRow = "RNBQKBNR";

    // sets up the inital board with pieces in original position
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if(i == 0){
                theDisplay[i][j] = firstRow[j]; 

            } else if(i == 7){
                theDisplay[i][j] = lastRow[j]; 

            }else if(i == 1 ){
                theDisplay[i][j] = 'p'; 

            } else if( i == 6){
                theDisplay[i][j] = 'P'; 

            } else if ((i + j) % 2 == 0){
                theDisplay[i][j] = ' '; 

            } else{ 
                theDisplay[i][j] = '_'; 
            }
        }
    }

}

void TextDisplay::notify(Board &board) {

     for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if(board.getPiece(i, j).getPieceType() != PieceType::Empty) {
                theDisplay[i][j] = board.getPiece(i, j).getLetter();

            } else {
                if ((i + j) % 2 == 0) {
                    theDisplay[i][j] = ' '; 

                } else { 
                    theDisplay[i][j] = '_'; 
                }
            }
        }
     }
    
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    int num = 8; 
  // printing the display 
  for (auto row : td.theDisplay) { 
    out << num-- << " "; 
    for (char col : row) {
        out << col;
    }
    out << '\n';
  }
  out << "\n  abcdefgh" << endl; 
  
  return out;

}
