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
	int row, column, animesteptotal, animestep;
    int gemtype;
	bool selected;

public:
	// ----------------------------------------------------------------------------------------------------------------------------
	Gem();
	Gem(int row, int column, RenderWindow* window);
	//  ----------------------------------------------------------------------------------------------------------------------------

	void setrow(int row) { this->row = row; }
	int getrow() { return row;}
	void setcolumn(int column) { this->column = column; }
	int getcolumn() { return column; }
	void setgemtype(int gemtype) { this->gemtype = gemtype; }
	virtual int getgemtype() = 0;
	// this function draws a gem based on its type and position;
	virtual void draw(int column, int row) = 0;
	void draw_on_grid();
	void drawanimatedposition(int animestep);
	void setwindow(RenderWindow& window) {this->window = &window;}
	bool getselect() { return selected; }
	void select() { selected = true; }
	void deselect() { selected = false; }
	~Gem();
};