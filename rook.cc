#include "rook.h"
#include "board.h"

Rook::Rook(Color color) : Piece (color, PieceType::Rook) {}

bool Rook::validMove(Board &board, Coordinate start, Coordinate end) {
    // if the square is not empty and contains the same color
    if ((board.getPiece(end.xPos, end.yPos).getPieceType() != PieceType::Empty) &&
        (board.getPiece(end.xPos, end.yPos).getColor() == color)) {
            return false;
    }

    // if its not a straight line return false nsince a rook can only move straight horizontally or vertically
    if (!(start.xPos == end.xPos || start.yPos == end.yPos)) {
        return false;
    } 

    // if (selfCheck (board, end)) {
    //     return false;
   // }

    //checking for if any squares are blocked in between
    int rowsInBetw = end.xPos - start.xPos;
    int colsInBetw = end.yPos - start.yPos;

    int midRow = (rowsInBetw == 0) ? 0 : rowsInBetw/abs(rowsInBetw);
    int midCol = (colsInBetw == 0) ? 0 : colsInBetw/abs(colsInBetw);
    int currRow = start.xPos + midRow;
    int currCol = start.yPos + midCol;

    while (!(currRow == end.xPos && currCol == end.yPos)) {
        if (board.getPiece(currRow, currCol).getPieceType() != PieceType::Empty) {
            return false;
        }
        currRow += midRow;
        currCol += midCol;
    }

    return true;
}

char Rook::getLetter() {

    if(color == Color::White) {
        return 'R'; 
    } else {
        return 'r'; 
    }

}
