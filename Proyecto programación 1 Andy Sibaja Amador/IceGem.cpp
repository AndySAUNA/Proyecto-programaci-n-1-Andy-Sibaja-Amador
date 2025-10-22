#include "IceGem.h"

IceGem::IceGem()
{
	gemtype = 7;
}
void IceGem::draw(int column, int row) {
	if (gemtype == 7) {
		RectangleShape shape(Vector2f(70.f, 70.f));
		Color test(127, 255, 212);
		shape.setFillColor(test);
		shape.setOutlineColor(Color::Black);
		shape.setOutlineThickness(5.f);
		shape.setPosition(Vector2f((column + 5.f), (row + 5.f)));
		window->draw(shape);
	}
}

IceGem::~IceGem()
{
}
