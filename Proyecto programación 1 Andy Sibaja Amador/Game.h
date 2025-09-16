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
	int selx;
	int sely;
	Font font;
public:
	Game (RenderWindow &window) {
		selx = 9;
		sely = 9;
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
		text1.setString("Score: " + to_string(score));
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
	void buttonpressed(){
		bool mouseButtonPressed = false;

		}
	void select(int x, int y) {
		gboard->conprintboard();
		if (x == selx && y == sely) {//if the same gem position is selected again, it deselects it
			cout << "deselected" << endl;
			selx = 9;
			sely = 9;
			firstselect = true;
			gboard->resetxy12();
		}
		else if (firstselect == true) {//first gem selection
			gboard->resetxy12();
			gboard->setxy1(x, y);
			selx = x;
			sely = y;
			firstselect = false;
			cout << "first select, selected: " << x << "," << y << endl;
		}
		else if (firstselect == false) {//second gem selection step
			cout << "second select, selected: " << x << "," << y << endl;
			cout << "first select was: " << selx << "," << sely << endl;
			if (gboard->checkvalidmove1(selx, sely, x, y) == true) {
				cout << "valid move" << endl;
				gboard->setxy12(selx, sely, x, y);
				selx = 9;
				sely = 9;
				firstselect = true;

				//if (gboard->checkvalidmove2() == true) { // this checks if the move creates a match and processes the move if it does

				//	score += gboard->countmatches(gboard->detectmatches(gboard->getboard()));
				//	moves--;
				//}
				//else {
				//	cout << "error in checkvalidmove2" << endl;
				//}
			
			}
			else if (gboard->checkadyasent(selx, sely, x, y) == false) {//if the second selection is not adyasent to the first, it becomes the new first selection
				gboard->resetxy12();
				gboard->setxy1(x, y);
				selx = x;
				sely = y;
				firstselect = false;
				cout << "first select, selected: " << x << "," << y << endl;
			}
			else {//if the move is invalid, it resets the selection to first select
				gboard->resetxy12();
				gboard->setxy1(x, y);
				selx = x;
				sely = y;
				firstselect = false;
				cout << "first select, selected: " << x << "," << y << endl;
			}
		}
		
	}
	void select2() {

	}
	//void playmove() {
	//	//to be implemented
	//	int x1, y1, x2, y2;
	//	x1 = 0; y1 = 0; x2 = 0; y2 = 0;
	//	//mous detections to be implemented
	//	
	//	if (gboard->checkvalidmove1(x1, y1, x2, y2, gboard->getboard()) == true) {
	//		while (gboard->deletematches() == true) {

	//		}
	//		moves--;
	//	}
	//	else {

	//	}
	//destructor
	~Game() {
		delete gboard;
	}

};