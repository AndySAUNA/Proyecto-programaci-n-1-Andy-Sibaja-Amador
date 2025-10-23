#include "Gem.h"

Gem::Gem()
{
	animestep = 0;
	animesteptotal = 30;
	window = nullptr;
	row = 9;
	column = 9;
	gemtype = 0;
	selected = false;
}

Gem::Gem(int row, int column, RenderWindow* window)
{
	this->row = row;
	this->column = column;
	this->window = window;
	selected = false;
	animestep = 0;
	animesteptotal = 30;
	row = 9;
	column = 9;
	gemtype = 0;
}
void Gem::draw_on_grid()
{
	try {
		if (row == 8 && column == 8) { throw 1; }
		float dcolumn = column * 75.f + 200.f;
		float drow = row * 75.f;
		draw(dcolumn, drow);
	}
		catch (int error) {
			if (error == 1) { cout << "uninitialized " << endl; }
		}
}
void Gem::drawanimatedposition(int animestep)
{
	float dcolumn = (column * 75.f + 200.f);
	float drow = ((row * 75.f) - 75 + ((75/animesteptotal) *animestep));
	draw(dcolumn, drow);
}
Gem::~Gem()
{
	window = nullptr;
}