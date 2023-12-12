#include "game.h"
#include <string>
#include <iostream>
#include "subject.h"

using namespace std;

Game::Game() {}

// getter methods:
PieceType Game::getPieceType (int x, int y) {
    return board.getPiece(x, y).getPieceType();
}

State Game::getState() {
    return gameState;
}

float Game::getScore(Color currentTurn) {
    return (currentTurn == Color::White) ? whitePlayerScore : blackPlayerScore;
}


PlayerType Game::determinePlayerType(string input){
    if (input == "human") {
        return hm; 
    } else if (input == "computer1") {
        return CompLev1; 
    } else if (input == "computer2") {
        return CompLev2; 
    } else if (input == "computer3") {
        return CompLev3; 
    } else if (input == "computer4") {
        return CompLev4; 
    } else{
        throw invalid_argument("Player type is not correct!"); 
    }
}

void Game::setPlayerTypes() {
    string p1Type, p2Type;
    std::cin >> p1Type >> p2Type; 

    whitePlayerType = determinePlayerType(p1Type); 
    blackPlayerType = determinePlayerType(p2Type); 

    // If Human 
    if (whitePlayerType == 0) {
        whitePlayer = std::make_unique<Human>(Color::White);

    } else if (whitePlayerType == 1) {
        whitePlayer = std::make_unique<Level1>(Color::White);

    } else if (whitePlayerType == 2) {
        whitePlayer = std::make_unique<Level2>(Color::White);

    } else if (whitePlayerType == 3) {
        whitePlayer = std::make_unique<Level3>(Color::White);
    }
    
    if (blackPlayerType == 0) {
        blackPlayer = std::make_unique<Human>(Color::Black);

    } else if (blackPlayerType == 1) {
        blackPlayer = std::make_unique<Level1>(Color::Black);
    } else if (blackPlayerType == 2) {
        blackPlayer = std::make_unique<Level2>(Color::Black);

    } else if (blackPlayerType == 3) {
        blackPlayer = std::make_unique<Level3>(Color::Black);

    }
}

// helper methods:
PieceType findPieceType (char c) {
    if (c == 'K' || c == 'k') {
        return PieceType::King;
    } else if (c == 'N' || c == 'n') {
        return PieceType::Knight;
    } else if (c == 'Q' || c == 'q') {
        return PieceType::Queen;
    } else if (c == 'B' || c == 'b') {
        return PieceType::Bishop;
    } else if (c == 'R' || c == 'r') {
        return PieceType::Rook;
    } else {
        return PieceType::Pawn;
    } 
}

void Game::switchCurrentPlayer() {
    currentTurn = (currentTurn == Color::White) ? Color::Black : Color::White;
}


void Game::resign() {  
    if (currentTurn == Color::White) {
        std::cout << "Black wins!" << endl;
        blackPlayerScore++;
    } else if (currentTurn == Color::Black) {
        std::cout << "White wins!" << endl;
        whitePlayerScore++;
    }
    cout << "Current Score:" << endl;
    cout << "White: " << getScore(Color::White) << endl;
    cout << "Black: " << getScore(Color::Black) << endl;
    gameState = State::won;
}

// determines the pieces type
void Game::charPiece (char piece, Color& color, PieceType& piece_type) {
    char pieces [2][6] = {{'K', 'N', 'Q', 'B', 'R', 'P'},
                        {'k', 'n', 'q', 'b', 'r', 'p'}};
    
    if (piece >= 'a' && piece <= 'z') {
        color = Color::Black; 
    } else {
        color = Color::White;
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (piece == pieces [i][j]) {
                piece_type = findPieceType(piece);
                return;
            }
        }
    }
   
    throw (invalid_argument ("Piece Type is invalid"));
}


// code to run when user enters setupMode
void Game::setupMode () {
    std::cout << "You are now in Setup Mode:" << endl;
    gameState = State::inGame;
    if (!boardSetUp) {board.emptySetup();}
    //board.notifyObservers(board);
    string input;

    while (true) {  
        board.notifyObservers(board);
        cout << board << endl;

        try {
            cin >> input;
            cout << endl;
            cout << endl;
            if (input == "+") {
                string piece, pos;
                cin >> piece >> pos;
                if (piece.length() != 1) {
                    throw (invalid_argument ("Wrong piece type"));
                }
                
                Color color;
                PieceType piece_type;
    
                int x =  '8' - pos[1];
                int y =  pos[0] - 'a'; 

                charPiece(piece[0], color, piece_type);
                // if (getPieceType(x, y) != PieceType::Empty) {
                    board.setPiece(x, y, piece_type, color);
                // }
            } else if (input == "-") {
                string pos;
                cin >> pos;
                
                int x =  '8' - pos[1];
                int y =  pos[0] - 'a'; 

                if (getPieceType(x, y) != PieceType::Empty) {
                    board.setPiece(x, y, PieceType::Empty, Color::EmptyCol);
                }
            } else if (input == "=") {
                string color;
                cin >> color;
                if (color == "white") {
                    currentTurn = Color::White;
                } else if (color == "black") {
                    currentTurn = Color::Black;
                } else {
                    throw (invalid_argument ("Invalid player type"));
                }
            } else if (input == "done") {
                if (board.isValidSetup()) {
                    // board.updateAllPieceValidMoves();
                    if (board.isStalemate(((currentTurn == Color::White) ? Color::White : Color::Black))) {
                        cout << "Invalid, with this board the player to go first will be in stalemtate." << endl;
                        continue;
                    }
                    boardSetUp = true;
                    return;
                } else {
                throw (invalid_argument ("Invalid setup"));
                }
            }
        } catch (invalid_argument& exception) {
            cout << exception.what() << endl;
        }
    } 
    cout << board;
}
  
void Game::move() {
    if (currentTurn == Color::White) {
        whitePlayer->makeMove(board);
    } else  if (currentTurn == Color::Black) {
        blackPlayer->makeMove(board);
    }

    int row = (currentTurn == Color::White) ? 2 : 5;

    for (int i = 0; i < board.size; i++) {
        board.getPiece(row, i).enpassed = false;
    }

    Color opponentColor = board.getOpponentColor(currentTurn);
    
    if(board.isStalemate(opponentColor)) {
        cout << "StaleMate true" << endl; 
        gameState = State::stalemate;
    } else if (board.isCheckmate(opponentColor)) {
        gameState = State::won;
    } else if (board.isKingInCheck(opponentColor)) {
        cout << ((opponentColor == Color::White) ? "White" : "Black") << " is in check" << endl;
    }
}

void Game::setGraphics(bool tval) {
    board.setGraphics(tval);
    graphicOn = tval;
}

// main function to run when board and players are set and game is to be started
void Game::startGame() {
    setPlayerTypes();   // reading in the two types of players
    gameState = State::inGame;
    
    if (!boardSetUp) {
        board.basicSetup();
    }

    board.notifyObservers(board);
    cout << endl << board << endl;      // outputting textdisplay 

    while(gameState == State::inGame) {
    
        cout << (currentTurn == Color::White ? "White" : "Black") << "'s turn to move:" << endl;

        string cmd;

        cin >> cmd;
        if (cmd == "resign") {
            resign();
            break;
        } else if (cmd == "move") {
            move();
            cout << board; 
            
        }

        if (gameState == State::stalemate) {
            std::cout << "Stalemate!" << endl;
            whitePlayerScore += 0.5;
            blackPlayerScore += 0.5;

            // scores output when program ends, EOF or ctrl-D
            cout << "Current Score:" << endl;
            cout << "White: " << getScore(Color::White) << endl;
            cout << "Black: " << getScore(Color::Black) << endl << endl;

        } else if (gameState == State::won) {
            std::cout << "Checkmate! " << (currentTurn == Color::White ? "White" : "Black") << " wins!" << endl;
            (currentTurn == Color::White) ? whitePlayerScore++ : blackPlayerScore++;
              // scores output when program ends, EOF or ctrl-D
            cout << "Current Score:" << endl;
            cout << "White: " << getScore(Color::White) << endl;
            cout << "Black: " << getScore(Color::Black) << endl << endl;
        } else {
           switchCurrentPlayer();
        }
    }

    boardSetUp = false;
}

