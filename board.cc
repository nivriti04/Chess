#include "board.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "observer.h"
#include "emptyPiece.h"


using namespace std;

Board::Board() : td {nullptr}, gd{nullptr} {}


Board::~Board() {
  // this->detach(td); 
  // this->detach(gd);

  this->detach(td.get());
  td.reset();

  this->detach(gd.get());
  td.reset();

  if (gd != nullptr) {
    // del gd;
    gd = nullptr;
  }
  // del gd;

  if (td != nullptr) {
    // del td;
    td = nullptr;
  } 
  // del td;
}


void Board::setGraphics(bool tval) {
  graphicsOn = tval;
}

vector<Board::Moves> Board::getAllMoves(Color team){

  vector<Moves> allMoves;

  // going through all the pieces in the board 
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      Piece::Coordinate startCorr = {i, j};
      Piece& piece = getPiece(i, j); 

      // if not our team then we do not need to consider the moves of the piece 
      if(getPiece(i, j).getColor() != team){
        continue; 
      }

      for(int m = 0; m < size; m++){

        for(int n = 0; n < size; n++){

          Piece::Coordinate endCorr = {m, n};
          getPiece(m,n).setCapture(false); // resetting 

            if(getPiece(m, n).getColor() == team){
              continue; 
            } 

            // cout << "Start: " << i << " " << j << endl;
            // cout << "End: " << m << " " << n << endl;
            if(piece.validMove(*this, startCorr, endCorr)){
              if(!piece.selfCheck(*this, endCorr)){

              Moves newMove; 
              newMove.start = startCorr; // starting coordinate of this move  
              newMove.end = endCorr;  // ending coordinate of this move

                // checking if the move results in a capture 
                if (getPiece(m,n).getPieceType() != PieceType::Empty) {
                    newMove.capture = true; 
                    getPiece(m,n).setCapture(true); 
                } else {
                    newMove.capture = false; 
                }

                allMoves.emplace_back(newMove); 
              }

            }
          }
        }
      }
    }


    return allMoves; 
}

Color Board:: getOpponentColor(Color color) {
  return (color == Color::Black) ? Color::White : Color::Black;
}

Piece::Coordinate Board::getKingLocation(Color kingColor) const{

  Piece::Coordinate returnCoord; 
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {    
      if (pieces[i][j]->getColor() == kingColor && pieces[i][j]->getPieceType() == PieceType::King) {
        returnCoord.xPos = i;
        returnCoord.yPos = j;
        return returnCoord;
      }
    }
  }
  return {0,0};
}

bool Board::isKingInCheck(Color kingColor) {
  Piece::Coordinate kingCoords = getKingLocation(kingColor);
  Color opponentColor = getOpponentColor(kingColor);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {    
      if (pieces[i][j]->getColor() == opponentColor &&
          pieces[i][j]->getPieceType() != PieceType::King && 
          pieces[i][j]->validMove(*this, {i ,j}, kingCoords)) {
        return true;
      }
    }
  }

  return false;
}

bool Board::isCheckmate(Color kingColor){
  // cout << *this << endl;


  if (!isKingInCheck (kingColor)) return false;

  vector<Board::Moves> mv = getAllMoves(kingColor);
  int s = mv.size();

  if (s == 0){
      return true; 
  }

  return false;
}

bool Board::isStalemate(Color kingColor){
  if (isKingInCheck(kingColor)) return false;

  if (getAllMoves(kingColor).size() == 0){
      return true; 
    }
  return false;
}

Piece& Board::getPiece(int x, int y) const{
  return *pieces[x][y]; 
}

void Board::updateAllPieceValidMoves() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (getPiece(i,j).getPieceType() != PieceType::Empty) {
        getPiece(i,j).updateValidMoves(*this); 
      }
    }
  } 
}


void Board::updatePiece(int oldX, int oldY, int newX, int newY){
  unique_ptr<Piece> empty_piece = make_unique<EmptyPiece>(Color::EmptyCol);
  unique_ptr<Piece> temp; 
  temp = (std::move(pieces[oldX][oldY])); 

  pieces[oldX][oldY] = (std::move(empty_piece));
  pieces[newX][newY] = (std::move(temp));
  pieces[oldX][newX]->setCoordinates(oldX, newX);
  pieces[newX][newY]->setCoordinates(newX, newY);
}

void Board::switchPieces(int oldX, int oldY, int endX, int endY, Color col, PieceType pt, bool mv, bool enp) {
   unique_ptr<Piece> old_piece; 
  if (pt == PieceType::Pawn) {
      old_piece = make_unique<Pawn>(col);
    } else if (pt == PieceType::Knight) {
      old_piece = make_unique<Knight>(col);
    } else if (pt == PieceType::Bishop) {
      old_piece = make_unique<Bishop>(col);
    } else if (pt == PieceType::Rook) {
      old_piece = make_unique<Rook>(col);
    } else if (pt == PieceType::Queen) {
      old_piece = make_unique<Queen>(col);
    } else if (pt == PieceType::King) {
      old_piece = make_unique<King>(col);
    } else if (pt == PieceType::Empty) {
      old_piece = make_unique<EmptyPiece>(col);
    }


  unique_ptr<Piece> temp; 
  temp = (std::move(pieces[oldX][oldY])); 
  
  (*old_piece).setCoordinates(oldX, oldY);
  (*old_piece).setMoved(mv);
  (*old_piece).enpassed = enp;
  (*temp).setCoordinates(endX, endY);

  pieces[endX][endY] = (std::move(temp)); 
  pieces[oldX][oldY] = (std::move(old_piece));
}


void Board::setPiece(int x, int y, PieceType piece, Color color) {
  if (color != Color::White && color != Color::Black && color != Color::EmptyCol) {
    throw std::invalid_argument("addPiece: Invalid color");
  }

  unique_ptr<Piece> new_piece;
  if (piece == PieceType::Pawn) {
    new_piece = make_unique<Pawn>(color);
  } else if (piece == PieceType::Knight) {
    new_piece = make_unique<Knight>(color);
  } else if (piece == PieceType::Bishop) {
    new_piece = make_unique<Bishop>(color);
  } else if (piece == PieceType::Rook) {
    new_piece = make_unique<Rook>(color);
  } else if (piece == PieceType::Queen) {
    new_piece = make_unique<Queen>(color);
  } else if (piece == PieceType::King) {
    new_piece = make_unique<King>(color);
  } else if (piece == PieceType::Empty) {
    new_piece = make_unique<EmptyPiece>(color);
  } else {
    throw std::invalid_argument("The type of piece is not valid");
  }

  
  pieces[x][y] = (std::move(new_piece));
  getPiece(x ,y).setCoordinates(x, y);
}

bool Board::isValidSetup() {
  //check for the kings and queen logic
  int whiteKing = 0;
  int blackKing = 0;

  // if we have pawns at the first or last row
  for(int i = 0; i < size; ++i) {
    if ((pieces[0][i]->getPieceType() == PieceType::Pawn) ||  (pieces[7][i]->getPieceType() == PieceType::Pawn)) {
      return false;
    }
  }

  // check that there are exactly one king of each colour
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {      
      if (pieces[i][j]->getPieceType() == PieceType::King) {
        if (pieces[i][j]->getColor() ==  Color::Black) {
          ++blackKing;
        } else {
          ++whiteKing;
        }
      }
    }
  }

  if (whiteKing != 1) return false;
  if (blackKing != 1) return false;
 
  // check that kings are not in check
  if (isKingInCheck(Color::White)) {return false;};
  if (isKingInCheck(Color::Black)) {return false;};

  // if all above cases passed board is a valid setup
  return true;
}

// done
void Board::basicSetup(){

  // Setting the middle part of the board to empty pieces 
  for (int i = 2; i < size - 2; i++) {
    for (int j = 0; j < size; j++) {
      setPiece(i, j, PieceType::Empty, Color::EmptyCol);
      getPiece(i, j).curCoords.xPos = i;
    }
  }

  // set white pieces at the bottom
  for (int i = 0; i < size; i++) {
    setPiece(6, i, PieceType::Pawn, Color::White);
  }

  setPiece(7, 0, PieceType::Rook, Color::White);
  setPiece(7, 1, PieceType::Knight, Color::White);
  setPiece(7, 2, PieceType::Bishop, Color::White);
  setPiece(7, 3, PieceType::Queen, Color::White);
  setPiece(7, 4, PieceType::King, Color::White);
  setPiece(7, 5, PieceType::Bishop, Color::White);
  setPiece(7, 6, PieceType::Knight, Color::White);
  setPiece(7, 7, PieceType::Rook, Color::White);


  // set black pieces at the top 
  for (int i = 0; i < size; i++) {
    setPiece(1, i, PieceType::Pawn, Color::Black);
  }

  setPiece(0, 0, PieceType::Rook, Color::Black);
  setPiece(0, 1, PieceType::Knight, Color::Black);
  setPiece(0, 2, PieceType::Bishop, Color::Black);
  setPiece(0, 3, PieceType::Queen, Color::Black);
  setPiece(0, 4, PieceType::King, Color::Black);
  setPiece(0, 5, PieceType::Bishop, Color::Black);
  setPiece(0, 6, PieceType::Knight, Color::Black);
  setPiece(0, 7, PieceType::Rook, Color::Black);

  // GraphicsDisplay(xw);

  if (!td) {
    // td = new TextDisplay();
    // this->attach(td);

    td = make_unique<TextDisplay>();
    this->attach(td.get());
  }

  if (!gd && graphicsOn) {
    // gd = new GraphicsDisplay(xw);
    // this->attach(gd);

    gd = std::make_unique<GraphicsDisplay>(xw);
    this->attach(gd.get());
  }
}

void Board::emptySetup() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      setPiece(i, j, PieceType::Empty, Color::EmptyCol);
    }
  }

  if (!td) {
    // td = new TextDisplay();
    // this->attach(td);

    td = make_unique<TextDisplay>();
    this->attach(td.get());    
  }

if (!gd && graphicsOn) {
    // gd = new GraphicsDisplay(xw);
    // this->attach(gd);

    gd = std::make_unique<GraphicsDisplay>(xw);
    this->attach(gd.get());
  }
}

ostream &operator<<(ostream &out, const Board &b) {
  // outputting the text display
  out << *b.td; 
  return out; 
}


