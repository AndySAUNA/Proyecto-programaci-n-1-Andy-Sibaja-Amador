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
	
	RectangleShape rect2(Vector2f(50.f, 50.f));
	rect.setFillColor(Color::White);
	rect.setOutlineColor(test);
	rect.setOutlineThickness(5.f);
	rect.setPosition(Vector2f((column), (row)));

	window->draw(rect);
	window->draw(rect2);
}

IceGem::~IceGem()
{
}
