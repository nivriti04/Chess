#include "graphicsdisplay.h"
#include "board.h"
#include "window.h"
#include <X11/Xlib.h>
#include <iostream>

// Ctor 
GraphicsDisplay::GraphicsDisplay(Xwindow &xw): xw{xw} {}


void GraphicsDisplay::notify(Board &board){

    xw.fillRectangle(0, 0, 1024, 800, Xwindow::White);

    for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
		
            if ((i + j) % 2 == 0) {
                xw.fillRectangle((i * 128), (100 * j), 128, 100, Xwindow::White);
            } else {
                xw.fillRectangle((i * 128), (100 * j), 128, 100, Xwindow::Blue);
            }
        }
    }

    // Redraw the board and pieces
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board.getPiece(i, j).getPieceType() != PieceType::Empty) {
                if (i == 0) {
                    xw.drawString((j + 0.5) * 128, 50, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 1) {
                    xw.drawString((j + 0.5) * 128, 150, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 2) {
                    xw.drawString((j + 0.5) * 128, 250, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 3) {
                    xw.drawString((j + 0.5) * 128, 350, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 4) {
                    xw.drawString((j + 0.5) * 128, 450, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 5) {
                    xw.drawString((j + 0.5) * 128, 550, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 6) {
                    xw.drawString((j + 0.5) * 128, 650, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                } else if (i == 7) {
                    xw.drawString((j + 0.5) * 128, 750, std::string(1, board.getPiece(i, j).getLetter()), 1, "lucidasans-24");
                }
            }
        }
   }
}

// Dtor
GraphicsDisplay::~GraphicsDisplay(){}
