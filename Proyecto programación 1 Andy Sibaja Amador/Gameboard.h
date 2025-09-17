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
	int row1, column1, row2, column2;
public:
	Gameboard(RenderWindow& window) {
		srand((unsigned)time(0));
		row1 = 9;
		column1 = 9;
		row2 = 9;
		column2 = 9;
		this->window = &window;
		int i, j;
		board = new Gem * [8];
		for (i = 0; i < 8; i++) {
			board[i] = new Gem[8];
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				board[i][j].setrow(i);
				board[i][j].setcolumn(j);
				board[i][j].setgemtype(0);
				board[i][j].setwindow(window);
			}
		}
		randomizegameboard();
		for (i = 0; i < 8; i++) {
			cout << "row " << i;
			for (j = 0; j < 8; j++) {
				cout << "\t" << board[i][j].getgemtype();
			}
			cout << endl;
		}

		
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
		//draws red square around selected gem
		if (row1 != 9 && column1 != 9) {
			lightup(row1, column1);
			//rect2.setPosition(Vector2f((column1 * 75.f + 200.f), (row1 * 75.f)));
			//window->draw(rect2);
		}
		if (row1 != 9 && column1 != 9 && row2 != 9 && column2 != 9) {
			lightup(row1, column1);
			lightup(row2, column2);
			//rect2.setPosition(Vector2f((column1 * 75.f + 200.f), (row1 * 75.f)));
			//window->draw(rect2);
			//rect2.setPosition(Vector2f((column2 * 75.f + 200.f), (row2 * 75.f)));
			//window->draw(rect2);

		}
		//draws the gems on the board
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j].draw();
			}
		}
	}
	//this function sets the coordinates of the first and second selection
	void setxy12(int row1, int column1, int row2, int column2) {
		this->row1 =row1;
		this->column1 = column1;
		this->row2 = row2;
		this->column2 = column2;
	}
	void setxy1(int row, int column) {
		row1 = row;
		column1 = column;
	}
	void resetxy12() {
		row1 = 9;
		column1 = 9;
		row2 = 9;
		column2 = 9;
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
	bool** detectmatches(Gem** board) {
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
		for (i = 0; i < 8; i++) {
			for (j = 1; j < 7; j++) {
				//testing for row matches
				if ((board[i][j].getgemtype() == board[i][j - 1].getgemtype()) && (board[i][j].getgemtype() == board[i][j + 1].getgemtype()) && (board[i][j].getgemtype() != 0)) {
					fakeboard[i][j] = true;
					fakeboard[i][j + 1] = true;
					fakeboard[i][j - 1] = true;
				}
				//testing for column matches
				if ((board[j][i].getgemtype() == board[j - 1][i].getgemtype()) && (board[j][i].getgemtype() == board[j + 1][i].getgemtype()) && (board[i][j].getgemtype() != 0)) {
					fakeboard[j][i] = true;
					fakeboard[j - 1][i] = true;
					fakeboard[j + 1][i] = true;
				}
			}
		}
		return fakeboard;
	}
	// this function deletes matches on the board and returns true if matches were found
	bool deletematches() {
		bool** fakeboard = detectmatches(board);
		int i, j;
		resetxy12();
		bool matchesfound = false;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (fakeboard[i][j] == true) {
					lightup(i, j);
					board[i][j].draw();
				}
			}
		}
		window->display();
		this_thread::sleep_for(chrono::milliseconds(500));
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (fakeboard[i][j] == true) {
					board[i][j].setgemtype(0);
					matchesfound = true;
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
	void lightup(int row, int column) {
		RectangleShape shape(Vector2f(70.f, 70.f));
		shape.setFillColor(Color::Red);
		shape.setOutlineColor(Color::Black);
		shape.setOutlineThickness(5.f);
		shape.setPosition(Vector2f((column * 75.f + 200.f), (row * 75.f)));
		window->draw(shape);
	}
	void gravity() {
		srand((unsigned)time(0));
		int i, j, f,t;
		bool clean;
		for (t = 0; t < 8; t++) {//runs the gravity operation 8 times to make sure all gems have fallen to the bottom
			clean = true;//on the start of a new run on the matrix it is assumed clean until proven otherwise
			for (f = 0; f < 8; f++) {//makes sure top row has active gems
				if (board[0][f].getgemtype() == 0) {
					board[0][f].setgemtype((rand() % 5) + 1);
					drawgameboard();
					window->display();
					this_thread::sleep_for(chrono::milliseconds(500));
				}
			}
			

			for (i = 0; i < 8; i++) {//for every row of the matrix
				for (j = 0; j < 8; j++) {//for every column of the matrix
					if (board[i][j].getgemtype() == 0 && i > 0) {//if entry is equal to 0 and isn't the top row, replace it with the entry of one row higher and eliminate the higher row entry
						board[i][j].setgemtype(board[i - 1][j].getgemtype());
						board[i - 1][j].setgemtype(0);
						clean = false;// clean is false because a entry north is now equal to 0
						drawgameboard();
						window->display();
						this_thread::sleep_for(chrono::milliseconds(500));
					}
				}
			}
		}
		if (clean == true) {}// if a pass shows that there wasn't a single coodrinate with a 0, then it is clean and the operation can stop
	}
	bool gravitybrake() {
		int i, j;
		bool clean;
		for (i = 0; i < 8; i++) {//for every column of the first row of the matrix
			clean = true;//on the start of a new run on the matrix it is assumed clean until proven otherwise
			if (board[0][i].getgemtype() == 0) {//if entry is equal to 0 and isn't the top row, return false
				clean = false;
			}
		}
		return clean;//will give true if top row is full, false if not
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
			if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2))) {
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
		int i, j;
		//make a temp board to test the swap on
		Gem** temp = new Gem * [8];
		for (i = 0; i < 8; i++) {
			temp[i] = new Gem[8];
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				temp[i][j].setrow(i);
				temp[i][j].setcolumn(j);
				temp[i][j].setgemtype(board[i][j].getgemtype());
			}
		}
		//this part swaps the gems in the temporary board
		int t1, t2;
		t1 = temp[row1][column1].getgemtype();
		t2 = temp[row2][column2].getgemtype();
		temp[row1][column1].setgemtype(t2);
		temp[row2][column2].setgemtype(t1);
		//this part checks if the swap creates a match
		bool** ogfakeboard = detectmatches(board);

		cout << "ogfakeboard is: " << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << ogfakeboard[i][j] << "\t";
			}
			cout << endl;
		}
		for (int i = 0; i < 8; i++) {
			delete[] ogfakeboard[i];
		}
		delete[] ogfakeboard;
		bool** fakeboard = detectmatches(temp);
		cout << "t1 and t2 are: " << t1 << "," << t2 << endl;
		cout << "sx1,sy1 and sx2,sy2 are: " << row1 << "," << column1 << " and " << row2 << "," << column2 << endl;
		cout << "fakeboard is: " << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << fakeboard[i][j] << "\t";
			}
			cout << endl;
		}
		/*cout << "Press enter to continue" << endl;
		cin.get();*/

		if (countmatches(fakeboard) > 0) {
			//if a match is found, swap the real board and delete the temp and fakeboard and return true
			cout << "matches found" << endl;
			/*cout << "Press enter to continue" << endl;
			cin.get();*/
			board[row1][column1].setgemtype(t2);
			board[row2][column2].setgemtype(t1);
			for (int i = 0; i < 8; i++) {
				delete[] fakeboard[i];
				delete[] temp[i];
			}
			delete[] fakeboard;
			delete[] temp;
			/*cout << "Press enter to continue" << endl;
			cin.get();*/
			return true;
		}
		else {//if no match is found, just delete the temp and fakeboard and retrn false
			/*cout << "no matches found" << endl;
			cout << "Press enter to continue" << endl;
			cin.get();*/
			for (int i = 0; i < 8; i++) {
				delete[] fakeboard[i];
				delete[] temp[i];
			}
			delete[] fakeboard;
			delete[] temp;
			/*cout << "Press enter to continue" << endl;
			cin.get();	*/
			return false;
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