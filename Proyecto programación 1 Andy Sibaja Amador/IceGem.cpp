#include "IceGem.h"

IceGem::IceGem()
{
	gemtype = 7;
}
void IceGem::draw(int column, int row) {
	RectangleShape rect(Vector2f(70.f, 70.f));
	Color test(211, 211, 211);
	rect.setFillColor(test);
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(5.f);
	rect.setPosition(Vector2f((column + 5.f), (row + 5.f)));
	RectangleShape shape(Vector2f(30.f, 30.f));
	shape.setFillColor(Color::White);
	shape.setOutlineColor(Color::Red);
	shape.setOutlineThickness(5.f);
	shape.setPosition(Vector2f((column + 5), (row + 5)));
	window->draw(rect);
	window->draw(shape);
}

IceGem::~IceGem()
{
}
