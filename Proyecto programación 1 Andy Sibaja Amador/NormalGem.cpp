#include "NormalGem.h"
NormalGem::NormalGem()
{
	gemtype = (rand() % 5) + 1;
}
NormalGem::NormalGem(int row, int column, RenderWindow* window)
{
	this->row = row; this->column = column; this->window = window; gemtype = (rand() % 5) + 1;
}
void NormalGem::draw(int column, int row){
	try {
		if (window == nullptr) { throw 1; }
	if (selected == true) {
		Texture texture;
		if (!texture.loadFromFile("resources\\red glow 70.png")) { throw 2; }
		Sprite backgroundSprite;
		backgroundSprite.setTexture(texture);
		backgroundSprite.setPosition(column + 1.f, row + 1.f);
		window->draw(backgroundSprite);
	}
	
		if (gemtype == 1) {
				Texture texture;
				if (!texture.loadFromFile("resources\\gem 1 70.png")) { throw 2; }
				Sprite backgroundSprite;
				backgroundSprite.setTexture(texture);
				backgroundSprite.setPosition(column+1.f, row+1.f);
				window->draw(backgroundSprite);
			/*
			CircleShape shape(30.f);
			shape.setFillColor(Color::Red);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 5)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
			*/
			

		}

		else if (gemtype == 2) {
			Texture texture;
			if (!texture.loadFromFile("resources\\gem 2 70.png")) { throw 2; }
			Sprite backgroundSprite;
			backgroundSprite.setTexture(texture);
			backgroundSprite.setPosition(column + 1.f, row + 1.f);
			window->draw(backgroundSprite);
				/*
				CircleShape shape(30.f,3);
			shape.setFillColor(Color::Green);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 14)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
				*/
		}
		else if (gemtype == 3) {
			Texture texture;
			if (!texture.loadFromFile("resources\\gem 3 70.png")) { throw 2; }
			Sprite backgroundSprite;
			backgroundSprite.setTexture(texture);
			backgroundSprite.setPosition(column + 1.f, row + 1.f);
			window->draw(backgroundSprite);
			/*
			CircleShape shape(30.f, 4);
			shape.setFillColor(Color::Blue);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5.f), (row + 5.f)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
			*/
			
		}
		else if (gemtype == 4) {
			Texture texture;
			if (!texture.loadFromFile("resources\\gem 4 70.png")) { throw 2; }
			Sprite backgroundSprite;
			backgroundSprite.setTexture(texture);
			backgroundSprite.setPosition(column + 1.f, row + 1.f);
			window->draw(backgroundSprite);
			/*
			CircleShape shape(30.f, 5);
			shape.setFillColor(Color::Yellow);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5.f), (row + 10.f)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
			*/
			
		}
		else if (gemtype == 5) {
			Texture texture;
			if (!texture.loadFromFile("resources\\gem 5 70.png")) { throw 2; }
			Sprite backgroundSprite;
			backgroundSprite.setTexture(texture);
			backgroundSprite.setPosition(column + 1.f, row + 1.f);
			window->draw(backgroundSprite);
			/*
			CircleShape shape(30.f, 6);
			shape.setFillColor(Color::Cyan);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5.f), (row + 6.f)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
			*/
		}
		}
		catch(int error){
			if (error == 1) { cout << "error drawing gem: " << row << "'" << column << " window pointer is null" << endl; }
			if (error == 2) { cout << "error opening main menu texture" << endl; }
		}
}


