#include "Gem.h"

Gem::Gem()
{
	window = nullptr;
	row = 9;
	column = 9;
	gemtype = 0;
}

Gem::Gem(int row, int column, int gemtype, RenderWindow* window)
{
	this->row = row;
	this->column = column;
	this->gemtype = gemtype;
	this->window = window;
}