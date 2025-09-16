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
	int sx1, sy1, sx2, sy2;
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
		randomizegameboard();
		sx1 = 9; 
		sy1 = 9; 
		sx2 = 9;
		sy2 = 9;
	}
	//this function draws the gameboard on the window
	
	void drawgameboard() {
		//make a aquamarine background squares for grid
		RectangleShape rect(Vector2f(75.f, 75.f));
		Color test(127, 255, 212);
		rect.setFillColor(test);
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(5.f);
		//make a red background squares for grid
		RectangleShape rect2(Vector2f(70.f, 70.f));
		rect2.setFillColor(Color::Red);
		rect2.setOutlineColor(Color::Black);
		rect2.setOutlineThickness(5.f);

		//ment to draw a 8x8 grid of squares on the right side of the window
		for (float i = 0; i < 8; i++) {
			for (float j = 0; j < 8; j++) {
				rect.setPosition(Vector2f((i * 75.f + 200.f), (j * 75.f)));
				window->draw(rect);
			}
		}
		if (sx1 != 9 && sy1 != 9) {
			rect2.setPosition(Vector2f((sx1 * 75.f + 200.f), (sy1 * 75.f)));
			window->draw(rect2);
		}
		if (sx1 != 9 && sy1 != 9 && sx2 != 9 && sy2 != 9) {
			rect2.setPosition(Vector2f((sx1 * 75.f + 200.f), (sy1 * 75.f)));
			window->draw(rect2);
			rect2.setPosition(Vector2f((sx2 * 75.f + 200.f), (sy2 * 75.f)));
			window->draw(rect2);
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j].draw();
			}
		}
		
	}
	//this function sets the coordinates of the first and second selection
	void setxy12(int x1, int y1, int x2, int y2) {
		sx1 = x1;
		sy1 = y1;
		sx2 = x2;
		sy2 = y2;
	}
	void setxy1(int x, int y) {
		sx1 = x;
		sy1 = y;
	}
	void resetxy12() {
		sx1 = 9;
		sy1 = 9;
		sx2 = 9;
		sy2 = 9;
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
			for (i = 0; i < 8; i++) {
				delete[] fakeboard[i];
			}
			delete[] fakeboard;
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
					}
				}
			}
		}
	
			if (clean == true) {  }// if a pass shows that there wasn't a single coodrinate with a 0, then it is clean and the operation can stop
	}
	bool checkadyasent(int x1, int y1, int x2, int y2) {
		if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2))) {
			return true;
		}
		else { return false; }
	}
	//this function checks valid move and returns true or false
	bool checkvalidmove1(int x1, int y1, int x2, int y2) {

		cout << "valid move test 0" << endl;
		if (x1 >= 0 && x1 <= 7 && y1 >= 0 && y1 <= 7 && x2 >= 0 && x2 <= 7 && y2 >= 0 && y2 <= 7) {
			cout << "valid move test 1" << endl;
			if ((x1 == x2 + 1 || x1 == x2 - 1)&&(y1==y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1==x2))) {
				cout << "valid move test 2" << endl;
				cout << "x1,y1: " << x1 << "," << y1 << " x2,y2: " << x2 << "," << y2 << endl;
				cout << "gem 1 is: " << board[x1][y1].getgemtype() << "gem 2 is: " << board[x2][y2].getgemtype() << endl;
				if (board[x1][y1].getgemtype() != board[x2][y2].getgemtype()) {
					cout << "valid move test 3" << endl;
					cout << "valid move" << endl;
					return true;
				}
				else { return false; }
			}
			else { return false; }
		}
		else { return false; }
	}
	bool checkvalidmove2() {
		//make a temp board to test the swap on
		Gem** temp = board;
		//this part swaps the gems in the temp board
		int t1, t2;
		t1 = temp[sx1][sy1].getgemtype();
		t2 = temp[sx2][sy2].getgemtype();
		temp[sx1][sy1].setgemtype(t2);
		temp[sx2][sy2].setgemtype(t1);
		//this part checks if the swap creates a match
		bool** fakeboard = detectmatches(temp);
		if (countmatches(fakeboard) > 0) {
			//if a match is found, swap the real board and delete the temp and fakeboard and return true
			t1 = board[sx1][sy1].getgemtype();
			t2 = board[sx2][sy2].getgemtype();
			board[sx1][sy1].setgemtype(t2);
			board[sx2][sy2].setgemtype(t1);
			for (int i = 0; i < 8; i++) {
				delete[] fakeboard[i];
				delete[] temp[i];
			}
			delete[] fakeboard;
			delete[] temp;
			return true;
		}
		else {//if no match is found, just delete the temp and fakeboard and retrn false
			for (int i = 0; i < 8; i++) {
				delete[] fakeboard[i];
				delete[] temp[i];
			}
			delete[] fakeboard;
			delete[] temp;
		}
	}
	void deletegem(int x, int y) {
		board[x][y].setgemtype(0);
	}
	void conprintboard() {
		int i, j;
		for (i = 0; i < 8; i++) {
			cout << "Row " << i << ": \t";
			for (j = 0; j < 8; j++) {
				std::cout << board[i][j].getgemtype() << "\t";
			}
			std::cout << std::endl;
		}
	}
	//destructor
	~Gameboard() {
		for (int i = 0; i < 8; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
};