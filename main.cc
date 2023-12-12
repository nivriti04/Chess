#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "game.h"
#include <utility>

using namespace std;

// arguments to decide visual mode or graphic mode //
// if first arg 0 then text if 1 then graphic //
int main(int argc, char* argv[]) {
    std::cout << "Chess Program Started" << endl;
    std::cout << "Type: game [Player Type] [Player Type] (to start a new game)" << endl;
    std::cout << "Valid Player Types: human, computer1, computer2, computer3" << endl << endl;

    std::cout << "Type: setup (to enter setup mode)" << endl;

    Game gm;
 
    // determines display type
    if (argc == 2) {
        istringstream iss {argv[1]};
        string displayType;
        iss >> displayType;
        gm.setGraphics(displayType == "g" ? true : false);
    }

    string cmd;

    while (cin >> cmd) {
        // enters setup mode
        if (cmd == "setup") {
            gm.setupMode();
            std::cout << "Type: game [Player Type] [Player Type] (to start a new game:)" << endl;
            std::cout << "Type: setup (to enter setup mode)" << endl; 
        }

        // determines player types and starts game
        if (cmd == "game") {
            gm.startGame();
            std::cout << "Type: game [Player Type] [Player Type] (to start a new game:)" << endl;
            std::cout << "Type: setup (to enter setup mode)" << endl << endl; 
        }

        if (cmd == "exit") {break;}

    }

    // scores output when program ends, EOF or ctrl-D
    cout << "Final Score:" << endl;
    cout << "White: " << gm.getScore(Color::White) << endl;
    cout << "Black: " << gm.getScore(Color::Black) << endl;
}
