#include "BombGem.h"
BombGem::BombGem() {
	gemtype = 6;
}

void BombGem::draw(int column, int row)
{
	if (gemtype == 0) {
		RectangleShape shape(Vector2f(70.f, 70.f));
		Color test(127, 255, 212);
		shape.setFillColor(test);
		shape.setOutlineColor(Color::Black);
		shape.setOutlineThickness(5.f);
		shape.setPosition(Vector2f((column + 5.f), (row + 5.f)));
		window->draw(shape);
	}
}

BombGem::~BombGem()
{
}
