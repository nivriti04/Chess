#include "king.h"
#include "board.h"

King::King(Color color) : Piece(color, PieceType::King) {}

bool KingIsDiagonal(int x1, int x2, int y1, int y2) {
    int xdistance = std::abs(x2 - x1);
    int ydistance = std::abs(y2 - y1);

    return xdistance == ydistance;
}

bool King::validMove(Board &board, Coordinate start, Coordinate end) {
    board.getPiece(start.xPos, start.yPos).setIsCastlingLeft(false);
    board.getPiece(start.xPos, start.yPos).setIsCastlingRight(false);

    if (((abs(start.xPos - end.xPos)) > 2) ||
        ((abs(start.yPos - end.yPos)) > 2)) {
            return false;
        }

    if ((start.xPos == end.xPos) && (start.yPos == end.yPos)) {
        return false;
    }

    int castleXStart = (color == Color::White) ? 7 : 0;
    int castleYStart = 4;
    int widthdiff = (abs(start.yPos - end.yPos));

    if((start.xPos == castleXStart && start.yPos == castleYStart) && // at king starting square
        (end.xPos == castleXStart) && // moving to the same row
        widthdiff == 2 && // moving two left or right
        (board.getPiece(start.xPos, start.yPos).hasMoved() == false)) { // havent moved yet
             
            int rook_colsInBetw, rook_midCol, king_midCol, king_colsInBetw, rook_end, king_end;
            bool left = false;
            bool right = false;

            if (start.yPos < end.yPos) {
                //where the king and rook will end up being
                rook_end = 'f' - 'a'; // so index 5
                king_end = 'g' - 'a'; //index 6
                right = true;
            } else {
                //where the king and rook will end up being
                rook_end = 'c' - 'a'; // so index 5
                king_end = 'd' - 'a'; //index 6
                left = true;
            }

            if (right == true) {
                if (castleXStart == 7) {
                    if ((board.getPiece(7, 7).getPieceType() != PieceType:: Rook) || (board.getPiece(7, 7).getColor() != Color::White) || 
                        (board.getPiece(7, 7).hasMoved() == true)) {
                        return false;
                   
                    }
                } else if (castleXStart == 0) {
                    if ((board.getPiece(0, 7).getPieceType() != PieceType:: Rook) || (board.getPiece(0, 7).getColor() != Color::Black) ||
                        (board.getPiece(0, 7).hasMoved() == true)) {
                        return false;
                   
                    }
                }
            } else if (left == true) {
                 if (castleXStart == 7) {
                    if ((board.getPiece(7, 0).getPieceType() != PieceType:: Rook) || (board.getPiece(7, 0).getColor() != Color::White) ||
                        (board.getPiece(7, 0).hasMoved() == true)) {
                        return false;
                    
                    }
                } else if (castleXStart == 0) {
                    if ((board.getPiece(0, 0).getPieceType() != PieceType:: Rook) || (board.getPiece(0, 0).getColor() != Color::Black) ||
                        (board.getPiece(0, 0).hasMoved() == true)) {
                        return false;
                   
                    }
                }
            } else if (left == true) {
                 if (castleXStart == 7) {
                    if ((board.getPiece(7, 0).getPieceType() != PieceType:: Rook) || (board.getPiece(7, 0).getColor() != Color::White) ||
                        (board.getPiece(7, 0).hasMoved() == true)) {

                        return false;
                    
                    }
                } else if (castleXStart == 0) {
                    if ((board.getPiece(0, 0).getPieceType() != PieceType:: Rook) || (board.getPiece(0, 0).getColor() != Color::Black) ||
                        (board.getPiece(0, 0).hasMoved() == true)) {

                        return false;
                   
                    }
                }

                //checking for if any squares are blocked in between
                rook_colsInBetw = rook_end - end.yPos;
                rook_midCol = (rook_colsInBetw == 0) ? 0 : rook_colsInBetw/abs(rook_colsInBetw);

                king_colsInBetw = king_end - start.yPos;
                king_midCol = (king_colsInBetw == 0) ? 0 : king_colsInBetw/abs(king_colsInBetw);

                int rook_curCol = end.yPos + rook_midCol;

                // if squares between rook's final and initial place are not vacant
                while (rook_curCol != rook_end) {
                    if (board.getPiece(end.xPos, rook_curCol).getPieceType() != PieceType::Empty) {

                        return false;
                    }
                    rook_curCol += rook_midCol;
                }

                //Coordinate to calculate the cooordinates of the middle square
                Coordinate midCoord;
                if (right == true) {
                    midCoord = {end.xPos - start.xPos, end.yPos - start.yPos};
                } else {
                    midCoord = {start.xPos - end.xPos, start.yPos - end.yPos};
                }
                
                int king_curCol = start.yPos + king_midCol;
                while (king_curCol != king_end) {
                    if (board.getPiece(start.xPos, king_curCol).getPieceType() != PieceType::Empty) {
                        return false;
                    } else if (board.isKingInCheck(color)) {
                        return false;
                    } else if (selfCheck(board, end)) {
                        return false;
                    } else if (selfCheck(board, midCoord)) {
                        return false;
                    }

                    king_curCol += king_midCol;
                }

            }

                //checking for if any squares are blocked in between
                rook_colsInBetw = rook_end - end.yPos;
                rook_midCol = (rook_colsInBetw == 0) ? 0 : rook_colsInBetw/abs(rook_colsInBetw);

                king_colsInBetw = king_end - start.yPos;
                king_midCol = (king_colsInBetw == 0) ? 0 : king_colsInBetw/abs(king_colsInBetw);

                int rook_curCol = end.yPos + rook_midCol;

                // if squares between rook's final and initial place are not vacant
                while (rook_curCol != rook_end) {
                    if (board.getPiece(end.xPos, rook_curCol).getPieceType() != PieceType::Empty) {}
                    rook_curCol += rook_midCol;
                }

                if (left) {
                    if ((board.getPiece(end.xPos, 1).getPieceType() != PieceType::Empty) ||
                        (board.getPiece(end.xPos, 2).getPieceType() != PieceType::Empty) ||
                        (board.getPiece(end.xPos, 3).getPieceType() != PieceType::Empty)) {
                            return false;
                        }
                }

                if (right) {
                    if ((board.getPiece(end.xPos, 5).getPieceType() != PieceType::Empty) ||
                        (board.getPiece(end.xPos, 6).getPieceType() != PieceType::Empty)) {
                            return false;
                        }
                }

                //Coordinate to calculate the cooordinates of the middle square
                Coordinate midCoord;
                if (right == true) {
                    midCoord = {start.xPos, ((end.yPos > start.yPos) ?  start.yPos + 1 : start.yPos - 1)};
                } else {
                    midCoord = {start.xPos, ((end.yPos > start.yPos) ?  start.yPos + 1 : start.yPos - 1)};
                }
                
                int king_curCol = start.yPos + king_midCol;
                while (king_curCol != king_end) {
                    if (board.getPiece(start.xPos, king_curCol).getPieceType() != PieceType::Empty) {
                        return false;
                    } else if (board.isKingInCheck(color)) {
                        return false;
                    } else if (selfCheck(board, end)) {
                        return false;
                    } else if (selfCheck(board, midCoord)) {
                        return false;
                    }

                    king_curCol += king_midCol;
                }

            if (right == true) {

                board.getPiece(start.xPos, start.yPos).setIsCastlingRight(true);
                return true;
            } else if (left == true) {
                board.getPiece(start.xPos, start.yPos).setIsCastlingLeft(true);
                return true;
            }
        } else if ((board.getPiece(end.xPos, end.yPos).getPieceType() == PieceType::Empty) ||
        (board.getPiece(end.xPos, end.yPos).getColor() != color)) {
            int horMove = abs(end.xPos - start.xPos);
            int verMove = abs(end.yPos - start.yPos);

            // If not a normal Move 
            if ((horMove > 1 || verMove > 1)) {
                return false; 
            }  else {
                return (board.getPiece(start.xPos, start.yPos).getColor() != board.getPiece(end.xPos, end.yPos).getColor()); 
            }
        } 
    return false;
} 


   

char King::getLetter() {

    if (color == Color::White) {
        return 'K'; 
    } else {
        return 'k'; 
    }

}
