#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gameboard.h"

class Game {
private:
	int score;
	int moves;
	Gameboard* gboard;
	RenderWindow* window;
	bool selector;
	int selx;
	int sely;
public:
	Game(RenderWindow &window) {
		int selx = 9;
		int sely = 9;
		score = 0;
		moves = 20;
		this->window = &window;
		gboard = new Gameboard(window);
		gboard->randomizegameboard();
		selector = false;
	}
	void drawstats() {
		//to be implemented
	}
	void drawgame() {
		gboard->drawgameboard();
		drawstats();
	}
	void buttonpressed(){
		bool mouseButtonPressed = false;

		}
	bool select(int x, int y) {
		if (selector == false) {
			gboard->resetxy12();
			selx = x;
			sely = y;
			selector = true;
			return false;
		}
		else {
			if (x == selx && y == sely) {
				selx = 9;
				sely = 9;
				gboard->resetxy12();
				selector = false;
				return false;
			}
			else {
				gboard->setxy12(selx,sely,x,y);
				selx = 9; sely = 9;
				selector = false;
				return true;
			}
		}
		
	}
	void select2() {

	}
	void playmove() {
		//to be implemented
		int x1, y1, x2, y2;
		x1 = 0; y1 = 0; x2 = 0; y2 = 0;
		//mous detections to be implemented
		
		if (gboard->checkvalidmove(x1, y1, x2, y2, gboard->getboard()) == true) {
			while (gboard->deletematches() == true) {

			}
			moves--;
		}
		else {

		}
	}
	//destructor
	~Game() {
		delete gboard;
	}

};