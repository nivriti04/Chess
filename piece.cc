#include "board.h"
#include "piece.h"

Piece::Piece() {
    pieceType = PieceType::Empty;
}
Piece::~Piece(){}

Piece::Piece(Color &color, PieceType pieceType) : color {color}, pieceType {pieceType} {}

PieceType Piece::getPieceType () const {
    return pieceType;
}

bool Piece::hasCastled() {
    return castled;
}

bool Piece::isEnpassanting(Board& board, Coordinate end) {
    if ((color == Color::White) && (end.yPos == curCoords.yPos-1 && board.getPiece(curCoords.xPos - 1, curCoords.yPos - 1).enpassed == true)) {
        return true;
    }

    if ((color == Color::White) && (end.yPos == curCoords.yPos-1 && board.getPiece(curCoords.xPos + 1, curCoords.yPos + 1).enpassed == true)) {
        return true;
    }

    if ((color == Color::Black) && (end.yPos == curCoords.yPos+1 && board.getPiece(curCoords.xPos - 1, curCoords.yPos + 1).enpassed == true)) {
        return true;
    }

    if ((color == Color::Black) && (end.yPos == curCoords.yPos+1 && board.getPiece(curCoords.xPos + 1, curCoords.yPos + 1).enpassed == true)) {
        return true;
    }

    return false;
}

void Piece::setCastled() {
    castled = true;
}

bool Piece::getIsCastlingRight() {
    return castlingRight;
}

void Piece::setIsCastlingRight(bool val) {
    castlingRight = val;
}

bool Piece::getIsCastlingLeft() {
    return castlingLeft;
}

void Piece::setIsCastlingLeft(bool val) {
    castlingLeft = val;
}


Color Piece::getColor () const {
    return color;
}

void Piece::setPieceType(PieceType pt) {
    pieceType = pt; 
}

char Piece::getLetter(){
    return ' '; 
}

bool Piece::validMove (Board &board, Coordinate start, Coordinate end){
    cout << "entering pieces valid move" << endl; 
    return false; 
}

bool Piece::hasMoved() const {
    return move;
}

void Piece::setMoved(bool mv) {
    move = mv;
}

bool Piece::isEnpassant() {
    return false;
}

bool Piece::canPromote(){
    return false; 
}

void Piece::setPass(bool val){
    cout << "running set Pass in Piece" << endl; 
}

int Piece::getValidMoveCount() {
    return numValidMoves;
}

void Piece::setCoordinates(int x, int y) {
    curCoords = {x, y};
}

Piece::Coordinate Piece::getCoordinates() {
    return curCoords;
}

Piece::Coordinate Piece::getValidMove(int index) {
    if (index < 0 || index >= numValidMoves) {
        throw invalid_argument("Invalid index");
    }
    return allValidMoves[index];
}

void Piece::setCapture(bool val){
    canBeCaptured = val; 
 }

 bool Piece::getCapture(){
    return canBeCaptured; 
 }

bool Piece::selfCheck(Board& board, Coordinate end) {
    // going to location info
    PieceType pieceTakenType = board.getPiece(end.xPos, end.yPos).getPieceType();
    Color pieceTakenColor = board.getPiece(end.xPos, end.yPos).getColor();
    bool pieceTakenMoved = board.getPiece(end.xPos, end.yPos).hasMoved();
    bool enp = board.getPiece(end.xPos, end.yPos).enpassed; 
    
    Coordinate start = getCoordinates();
    
    bool plswork = getPieceType() == PieceType::Pawn && isEnpassanting(board,end);

    bool isSelfCheck;

    
    board.updatePiece(start.xPos, start.yPos, end.xPos, end.yPos); 
    
    if (plswork) {
        board.setPiece((color == Color::White) ? end.xPos - 1 : end.xPos + 1, end.yPos, PieceType::Empty, Color::EmptyCol);
    }

    if (board.isKingInCheck(getColor())) {
        isSelfCheck = true;
    } else {
        isSelfCheck = false;
    }

    
    board.switchPieces(end.xPos, end.yPos, start.xPos, start.yPos, pieceTakenColor, pieceTakenType, pieceTakenMoved, enp);

    if (plswork) {
        board.setPiece((color == Color::White) ? end.xPos - 1 : end.xPos + 1, end.yPos, PieceType::Empty, (color == Color::White) ? Color::White : Color::Black);
    }

    return isSelfCheck;
}

void Piece::updateValidMoves(Board& board) {
    numValidMoves = 0;
    allValidMoves.clear();
    for (int i = 0; i < board.size; i++) {
        for (int j = 0; j < board.size; j++) {
            Coordinate temp = {i, j};
            if (validMove(board, curCoords, temp)) {
                if (!selfCheck(board, temp)) {
                    allValidMoves.push_back(temp);
                    numValidMoves++;
                }
            }
        }
    }
}

