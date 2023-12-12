#include "emptyPiece.h"
#include "board.h"

EmptyPiece::EmptyPiece(Color color) : Piece(color, PieceType::Empty) {}

char EmptyPiece::getLetter() {
    return ' ';
}

bool EmptyPiece::validMove (Board &board, Coordinate start, Coordinate end) {
    return false;
}

