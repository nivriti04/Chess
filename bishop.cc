#include "bishop.h"
#include "board.h"

Bishop::Bishop(Color color) : Piece(color, PieceType::Bishop) {}

bool bishopIsDiagonal(int x1, int x2, int y1, int y2) {
    int xdistance = std::abs(x2 - x1);
    int ydistance = std::abs(y2 - y1);

    return xdistance == ydistance;
}

bool Bishop::validMove(Board &board, Coordinate start, Coordinate end) {
    // if the square is not empty or contains the same color
    if ((board.getPiece(end.xPos, end.yPos).getPieceType() != PieceType::Empty) ||
        (board.getPiece(end.xPos, end.yPos).getColor() == color)) {
            return false;
    }

    // if its not a diagonal
    if (!(bishopIsDiagonal(start.xPos, end.xPos, start.yPos, end.yPos))) {
        return false;
    } 

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

char Bishop::getLetter(){

    if(color == Color::White) {
        return 'B'; 
    } else {
        return 'b'; 
    }

}
