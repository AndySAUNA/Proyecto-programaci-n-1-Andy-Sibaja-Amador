#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;


class Gem {
protected:
	RenderWindow *window;
	int row, column;
    int gemtype;

public:
	// ----------------------------------------------------------------------------------------------------------------------------
	Gem();
	Gem(int row, int column, int gemtype, RenderWindow *window);
	void setrow(int row) { this->row = row; }
	int getrow() { return row;}
	void setcolumn(int column) { this->column = column; }
	int getcolumn() { return column; }
	void setgemtype(int gemtype) { this->gemtype = gemtype; }
	int getgemtype() { return gemtype; }
	// this function draws a gem based on its type and position;
	virtual void draw() = 0;
	void setwindow(RenderWindow& window) {this->window = &window;}
};