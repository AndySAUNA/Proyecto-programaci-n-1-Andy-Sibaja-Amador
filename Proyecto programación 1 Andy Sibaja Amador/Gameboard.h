#pragma once
#include <thread>
#include <chrono>
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
				board[i][j].setx(i);
				board[i][j].sety(j);
				board[i][j].setgemtype(0);
				board[i][j].setwindow(window);
			}
		}
	}
	//this function draws the gameboard on the window
	void drawgameboard() {
		RectangleShape rect(Vector2f(75.f, 75.f));
		Color test(127, 255, 212);
		rect.setFillColor(test);
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(5.f);
		//ment to draw a 8x8 grid of squares on the right side of the window
		for (float i = 0; i < 8; i++) {
			for (float j = 0; j < 8; j++) {
				rect.setPosition(Vector2f((i * 75.f + 200.f), (j * 75.f)));
				window->draw(rect);
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j].draw();
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
		bool** fakeboard = detectmatches(board);
		while (countmatches(fakeboard) != 0) {
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					if (fakeboard[i][j] == true) {
						board[i][j].setgemtype((rand() % 5) + 1);
					}
				}
			}
			fakeboard = detectmatches(board);
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
	// this function deletes matches on the board and returns true if matches were found
	bool deletematches() {
		bool** fakeboard = detectmatches(board);
		int i, j;
		bool matchesfound = false;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8;j++) {
				if (fakeboard[i][j] == true) {
					board[i][j].setgemtype(0);
					matchesfound = true;
					drawgameboard();
				}
			}
		}
		return matchesfound;
	}
	//this function takes a fakeboard and counts the amount of matches in it and returns the number
	int countmatches(bool** fakeboard) {
		int i, j;
		int matchesfound = 0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (fakeboard[i][j] == true) {
					matchesfound++;
				}
			}
		}
		return matchesfound;
	}
	// gives you the Gem class board matrix
	Gem** getboard() {
		return board;
	}
	//this function does the gravity effect
	void gravity() {

		srand((unsigned)time(0));
		int i, j, f, t;
		bool clean = false;

		for (t = 0; t < 8; t++) {//to repass matrix 8 times to ensure all gems are active
			clean = true;//on the start of a new run on the matrix it is assumed clean until proven otherwise
			for (f = 0; f < 8; f++) {//makes sure top row has active gems
				if (board[0][f].getgemtype() == 0) { board[0][f].setgemtype((rand() % 5) + 1); }
			}
			for (i = 0; i < 8; i++) {//for every row of the matrix
				for (j = 0; j < 8; j++) {//for every column of the matrix
					if (board[i][j].getgemtype() == 0 && i > 0) {//if entry is equal to 0 and isn't the top row, replace it with the entry of one row higher and eliminate the higher row entry
						board[i][j].setgemtype(board[i - 1][j].getgemtype());
						board[i - 1][j].setgemtype(0);
						clean = false;// clean is false because a entry north is now equal to 0
						drawgameboard();//this draws the gameboard as a move happens, o we can see the gravity effect
					}
				}
			}
		}
	
			if (clean == true) {  }// if a pass shows that there wasn't a single coodrinate with a 0, then it is clean and the operation can stop
	}
	//this function checks valid move and returns true or false
	bool checkvalidmove(int x1, int y1, int x2, int y2, Gem** board) {
		if (x1 == (1, 2, 3, 4, 5, 6, 7, 8) && y1 == (1, 2, 3, 4, 5, 6, 7, 8) && x2 == (1, 2, 3, 4, 5, 6, 7, 8) && y2 == (1, 2, 3, 4, 5, 6, 7, 8)) {
			if ((x1 == x2 + 1 || x1 == x2 - 1)&&(y1==y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1==x2))) {
				if ((board[x1][y1].getgemtype()) != (board[x2][y2].getgemtype())) {

					return true;
				}
				else { return false; }
			}
			else { return false; }
		}
		else { return false; }
	}
	void deletegem(int x, int y) {
		board[x][y].setgemtype(0);
	}
	//destructor
	~Gameboard() {
		for (int i = 0; i < 8; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
};