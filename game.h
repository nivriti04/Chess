
#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
#include "board.h"
#include "player.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "subject.h"
#include "human.h"
#include "computer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"

using namespace std;

enum State {inGame, stalemate, won};
enum PlayerType {hm = 0, CompLev1, CompLev2, CompLev3, CompLev4};


class Game {
    Board board;

    unique_ptr<Player> whitePlayer; 
    unique_ptr<Player> blackPlayer; 
    
    PlayerType whitePlayerType = hm;
    PlayerType blackPlayerType = hm;

    float whitePlayerScore = 0;
    float blackPlayerScore = 0;

    Color currentTurn = Color::White;

    State gameState = State::inGame;

    bool boardSetUp = false;

    bool graphicOn = false;
    
    unique_ptr<Observer> ob;

    //reads char passed to setUp mode and converts to pieces 
    void charPiece(char piece, Color& color, PieceType& piece_type);  
    
    public:
        Game();
        void setGraphics(bool tval); //sets the displays
        
        // getter methods:
        //returns the type of piece at a specific board index
        PieceType getPieceType (int x, int y);  
        
        State getState();

        void getCoords (string start, string end);
        
        float getScore(Color currentTurn);

        PlayerType determinePlayerType(string input);

        // set player types
        void setPlayerTypes();

        // helper methods:
        // done: switch the player turn
        void switchCurrentPlayer();

        void initialSetup();


        // might not need it:
        // void setScore();
        // void reset (int p1Type, int p2Type);
        // Coordinate convertStringToCoords(string s);
        // unique_ptr<Player> createPlayer (int side, int playerType);


        // key methods:

        // done: resigns player color
        void resign();

        // calls the players move method
        void move();

        // done: for setup mode command
        void setupMode();   

        // done: main running game function
        void startGame();
        
};

#endif
