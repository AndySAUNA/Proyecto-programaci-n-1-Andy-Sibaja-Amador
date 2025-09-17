#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Gameboard.h"
using namespace sf;
using namespace std;

class Game {
private:
	int score;
	int moves;
	Gameboard* gboard;
	RenderWindow* window;
	bool firstselect;
	int selrow;
	int selcolumn;
	Font font;
public:
	Game (RenderWindow &window) {
		selrow = 9;
		selcolumn = 9;
		score = 0;
		moves = 20;
		this->window = &window;
		gboard = new Gameboard(window);
		gboard->randomizegameboard();
		firstselect = true;
		font.loadFromFile("resources/fonts/OpenSans-Regular.ttf");
	}
	// draws score and moves
	void drawstats() {
		//prints score
		Text text1;
		text1.setFont(font);
		text1.setString("Score: " + to_string(score * 10));
		text1.setCharacterSize(24);
		text1.setFillColor(Color::White);
		text1.setPosition(40.f, 10.f);
		window->draw(text1);

		Text text2;
		text2.setFont(font);
		text2.setString("Moves: " + to_string(moves));
		text2.setCharacterSize(24);
		text2.setFillColor(Color::White);
		text2.setPosition(40.f, 40.f);
		window->draw(text2);
	}
	// game loop
	void drawgame() {
		drawstats();
		gboard->drawgameboard();
	}
	void select(int row, int column) {
		gboard->conprintboard();
		if (row == selrow && column == selcolumn) {//if the same gem position is selected again, it deselects it
			cout << "deselected" << endl;
			selrow = 9;
			selcolumn = 9;
			firstselect = true;
			gboard->resetxy12();
		}
		else if (firstselect == true) {//first gem selection
			gboard->resetxy12();
			gboard->setxy1(row, column);
			selrow = row;
			selcolumn = column;
			firstselect = false;
			cout << "first select, selected: " << row << "," << column << endl;
		}
		else if (firstselect == false) {//second gem selection step
			cout << "second select, selected: " << row << "," << column << endl;
			cout << "first select was: " << selrow << "," << selcolumn << endl;
			if (gboard->checkvalidmove1(selrow, selcolumn, row, column) == true) {
				cout << "valid move" << endl;
				gboard->setxy12(selrow, selcolumn, row, column);
				selrow = 9;
				selcolumn = 9;
				firstselect = true;
				if (gboard->checkvalidmove2() == true) { // this bit checks if the move creates a match and processes the move if it does
					cout << "gboard->checkvalidmove2() check passed"; 
					score += gemdestroyer();
					moves--;
					selrow = 9;
					selcolumn = 9;
					firstselect = true;
					gboard->resetxy12();

				}
				else { // this bit resets the selection if the move is invalid
					cout << "gboard->checkvalidmove2() check failed" << endl; 
					cout << "deselected" << endl;
					selrow = 9;
					selcolumn = 9;
					firstselect = true;
					gboard->resetxy12();
				}
			}
			else if (gboard->checkadyasent(selrow, selcolumn, row, column) == false) {//if the second selection is not adyasent to the first, it becomes the new first selection
				gboard->resetxy12();
				gboard->setxy1(row, column);
				selrow = row;
				selcolumn = column;
				firstselect = false;
				cout << "first select, selected: " << row << "," << column << endl;
			}
			else {//if the move is invalid, it resets the selection to first select
				gboard->resetxy12();
				gboard->setxy1(row, column);
				selrow = row;
				selcolumn = column;
				firstselect = false;
				cout << "first select, selected: " << row << "," << column << endl;
			}
		}
		
	}
	int gemdestroyer() {

		int destroyedgems = 0, mincounter = 0;
		destroyedgems += gboard->countmatches(gboard->detectmatches(gboard->getboard()));
		while (gboard->deletematches()==true) {
				window->clear();
				gboard->drawgameboard();
				gboard->gravity();
				destroyedgems += gboard->countmatches(gboard->detectmatches(gboard->getboard()));
				drawstats();
				window->display();
				this_thread::sleep_for(chrono::milliseconds(500));
		}
		return destroyedgems;
	}
	//destructor
	~Game() {
		delete gboard;
	}

};