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
	
	//if statements to make light gray or red background square for the gem's background
	RectangleShape rect(Vector2f(70.f, 70.f));
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(5.f);
	if (selected == false){
		Color test(211, 211, 211);
		rect.setFillColor(test);
		
	}
	if (selected == true) {
		rect.setFillColor(Color::Red);
	}
	
		if (gemtype == 1) {
			CircleShape shape(30.f);
			shape.setFillColor(Color::Red);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 5)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
		}
		if (gemtype == 2) {
			CircleShape shape(30.f,3);
			shape.setFillColor(Color::Green);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 14)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
		}
		if (gemtype == 3) {
			CircleShape shape(30.f, 4);
			shape.setFillColor(Color::Blue);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 5)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
		}
		if (gemtype == 4) {
			CircleShape shape(30.f, 5);
			shape.setFillColor(Color::Yellow);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 10)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
		}
		if (gemtype == 5) {
			CircleShape shape(30.f, 6);
			shape.setFillColor(Color::Cyan);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column + 5), (row + 6)));
			rect.setPosition(column, row);
			window->draw(rect);
			window->draw(shape);
		}
		}
		catch(int error){
			if (error == 1) { cout << "error drawing gem: " << row << "'" << column << " window pointer is null" << endl; }
		}
}


