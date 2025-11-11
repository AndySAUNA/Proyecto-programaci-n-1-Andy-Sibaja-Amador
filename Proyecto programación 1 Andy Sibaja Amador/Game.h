#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Gameboard.h"
using namespace sf;
using namespace std;
#include "Game.h"

// agregado para arreglar un error desconocido
class Gameboard;
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
	bool gameactive;
	bool endgame;
public:
	Game(RenderWindow& window);
	// draws score and moves ----------------------------------------------------------------------------------------------------------------------------
	void drawstats();
	// game loop ----------------------------------------------------------------------------------------------------------------------------
	void drawgame();
	// select function does the selecction process and iniciates moves ----------------------------------------------------------------------------------------------------------------------------
	void select(int row, int column);
	// makes the ice game ----------------------------------------------------------------------------------------------------------------------------
	void icegame();
	// this function orders the destrcution of gems ----------------------------------------------------------------------------------------------------------------------------
	int gemdestroyer();
	//ment for communication with the menu
	void setgameactive(bool b);
	//ment for communication with the menu
	bool getgameactive();
	void clean_game();
	bool endgamer();
	int getscore();
	void fast_game();
	void reset_game();
	void setendgame();
	//destructor ----------------------------------------------------------------------------------------------------------------------------
	~Game();
};