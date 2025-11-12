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
	try {
		Texture texture;
		if (!texture.loadFromFile("resources\\gem 6 70.png")) { throw 1; }
		Sprite backgroundSprite;
		backgroundSprite.setTexture(texture);
		backgroundSprite.setPosition(column, row);
		window->draw(backgroundSprite);
	}
	catch (int error) {
		if (error == 1) { cout << "error opening main menu texture" << endl; }
	}
	/*
	RectangleShape rect(Vector2f(70.f, 70.f));
	if (selected == false) {
		Color test(211, 211, 211);
		rect.setFillColor(test);
	}
	else { rect.setFillColor(Color::Red); }
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(5.f);
		rect.setPosition(Vector2f((column), (row)));

		CircleShape shape(28.f);
		shape.setFillColor(Color::Black);
		shape.setOutlineColor(Color::Red);
		shape.setOutlineThickness(2.f);
		shape.setPosition(Vector2f((column + 7), (row + 7)));
		window->draw(rect);
		window->draw(shape);
	*/
	
}

BombGem::~BombGem()
{
}
