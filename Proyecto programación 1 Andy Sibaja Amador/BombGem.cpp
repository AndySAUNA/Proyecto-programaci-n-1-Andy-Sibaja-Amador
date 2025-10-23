#include "BombGem.h"
BombGem::BombGem() {
	gemtype = 6;
}

BombGem::BombGem(int row, int column, RenderWindow* window)
{
	this->row = row; this->column = column; this->window = window; gemtype = 6;
}

void BombGem::draw(int column, int row)
{
	
		RectangleShape rect(Vector2f(70.f, 70.f));
		Color test(211, 211, 211);
		rect.setFillColor(test);
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(5.f);
		rect.setPosition(Vector2f((column + 5.f), (row + 5.f)));

		CircleShape shape(30.f);
		shape.setFillColor(Color::Black);
		shape.setOutlineColor(Color::Red);
		shape.setOutlineThickness(5.f);
		shape.setPosition(Vector2f((column + 5), (row + 5)));
		window->draw(rect);
		window->draw(shape);
}

BombGem::~BombGem()
{
}
