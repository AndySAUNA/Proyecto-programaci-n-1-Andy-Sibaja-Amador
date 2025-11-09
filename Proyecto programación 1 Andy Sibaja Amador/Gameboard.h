#pragma once
#include <thread>
#include <chrono>
#include "Gem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "NormalGem.h"
#include "IceGem.h"
#include "BombGem.h"
#include "Game.h"

using namespace std;
using namespace sf;

class Gameboard {
protected:
	RenderWindow* window;
	Gem*** board;
	int row1, column1, row2, column2,powergemcounter;
public:
	//constructor, creates the dynamic matrix and randomizes it's content with NormalGems ----------------------------------------------------------------------------------------------------------------------------
	Gameboard(RenderWindow& window);
	//this function draws the gameboard on the window ----------------------------------------------------------------------------------------------------------------------------
	void drawgameboard();
	//this function sets the coordinates of the first and second selection ----------------------------------------------------------------------------------------------------------------------------
	void setxy12(int row1, int column1, int row2, int column2);
	// sets the x and y coordinates for selection  ----------------------------------------------------------------------------------------------------------------------------
	void setxy1(int row, int column);
	//resets the x an y coordinates for selecction ----------------------------------------------------------------------------------------------------------------------------
	void resetxy12();
	// this function randomizes the gem types on the board ----------------------------------------------------------------------------------------------------------------------------
	void randomizegameboard();
	//this function detects mathces on the board ----------------------------------------------------------------------------------------------------------------------------
	bool** detectmatches(Gem*** board);
	// detect matches with a twist! it now adds the Kaboom!!!
	bool** detectmatcheswithbombs(Gem*** board);
	// this function deletes matches on the board and returns true if matches were found ----------------------------------------------------------------------------------------------------------------------------
	bool deletematches();
	int bomber(bool** fakeboard);
	int kaboom(int row, int column, bool** fakeboard);
	//this function takes a fakeboard and counts the amount of matches in it and returns the number ----------------------------------------------------------------------------------------------------------------------------
	int countmatches(bool** fakeboard);
	// gives you the Gem class board matrix ----------------------------------------------------------------------------------------------------------------------------
	Gem*** getboard();
	//this function does the gravity effect ----------------------------------------------------------------------------------------------------------------------------
	void lightup(int row, int column);
	// this function produces the gravity effect
	void gravity();
	// this function pulls everythin once ----------------------------------------------------------------------------------------------------------------------------
	bool gravitystep();
	bool gravitystep2();
	// this function generates the missing gems int he top part in a randomized manner ----------------------------------------------------------------------------------------------------------------------------
	void generatetop();
	//unrefranced, must consider deleting ----------------------------------------------------------------------------------------------------------------------------
	bool gravitybrake();
	//checks if 2 sets of coordinates are adyacent to each other and returns a boolean ----------------------------------------------------------------------------------------------------------------------------
	bool checkadyasent(int x1, int y1, int x2, int y2);
	//this function checks valid move and returns true or false ----------------------------------------------------------------------------------------------------------------------------
	bool checkvalidmove1(int x1, int y1, int x2, int y2);
	//tests the swap for combinations and returns true if any are found ----------------------------------------------------------------------------------------------------------------------------
	bool checkvalidmove2();
	//this function deletes a gem of set coordinates  ----------------------------------------------------------------------------------------------------------------------------
	void deletegem(int x, int y);
	//consol prints the board as a matrix of numbers corresponding to the gem type of each entry ----------------------------------------------------------------------------------------------------------------------------
	void conprintboard();
	//adds to the powergemcounter ----------------------------------------------------------------------------------------------------------------------------
	void addpowergems(int add) { powergemcounter = powergemcounter + add; }
	void addice(int x, int y);
	//destructor
	~Gameboard();
};