#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gameboard.h"

class Game {
private:
	int score;
	int moves;
	Gameboard* board;
	
public:
	Game(RenderWindow &window) {
		score = 0;
		moves = 20;
		board = new Gameboard(window);
		board->randomizegameboard();
	}
	~Game() {

	}

};