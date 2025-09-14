#pragma once
#include "Gem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Gameboard {
private:
	RenderWindow* window;
	Gem** board;
public:
	Gameboard(RenderWindow &window) {
		srand((unsigned)time(0));
		this->window = &window;
		int i, j;
		board = new Gem * [8];
		for(i = 0 ; i < 8; i++) {
			board[i] = new Gem[8];
		}
		for (i= 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				board[i][j].setpositionx(i);
				board[i][j].setpositiony(j);
				board[i][j].setgemtype(0);
			}
		}
	}
	//this function draws the gameboard on the window
	void drawgameboard() {
		int i, j;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				board[i][j].draw(*window, j, i);
			}
		}
	}
	// this function randomizes the gem types on the board
	void randomizegameboard() {
		int i, j;
		srand((unsigned)time(0));
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				board[i][j].setgemtype((rand() % 5) + 1);
			}
		}
	}
	//this function detects mathces on the board
	bool** detectmatches(Gem ** board) {
		bool** fakeboard;
		int i, j;
		fakeboard = new bool* [8];
		for (i = 0; i < 8; i++) {
			fakeboard[i] = new bool[8];
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				fakeboard[i][j] = false;
			}
		}
		for (i=0;i<8;i++) {
			for (j=1;j<7;j++) {
				//testing for row matches
				if ((board[i][j].getgemtype() == board[i][j-1].getgemtype()) && (board[i][j].getgemtype() == board[i][j+1].getgemtype()) && (board[i][j].getgemtype() != 0)) {
					fakeboard[i][j] = true;
					fakeboard[i][j+1] = true;
					fakeboard[i][j-1] = true;
				}
				//testing for column matches
				if ((board[j][i].getgemtype() == board[j-1][i].getgemtype()) && (board[j][i].getgemtype() == board[j+1][i].getgemtype()) && (board[i][j].getgemtype() != 0)) {
					fakeboard[j][i] = true;
					fakeboard[j-1][i] = true;
					fakeboard[j+1][i] = true;
				}
			}
		}
		return fakeboard;
	}
	//
	Gem** getboard() {
		return board;
	}
	//destructor
	~Gameboard() {
		for (int i = 0; i < 8; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
};