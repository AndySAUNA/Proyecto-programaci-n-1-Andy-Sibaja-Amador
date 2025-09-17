#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;


class Gem {
private:
	RenderWindow *window;
	int row, column;
	int gemtype;

public:
	Gem() {
		gemtype = 0;
		row = 0;
		column = 0;
		window = nullptr;
	}

	void setrow(int row) { this->row = row; }
	void setcolumn(int column) { this->column = column; }
	void setgemtype(int gemtype) { this->gemtype = gemtype; }
	int getgemtype() const { return gemtype; }
	// this function draws a gem based on its type and position;
	void draw () {
		if (gemtype == 0) {
			RectangleShape shape(Vector2f(70.f, 70.f));
			Color test(127, 255, 212);
			shape.setFillColor(test);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 200.f), (row * 75.f)));
			window->draw(shape);
		}
		if (gemtype == 1) {
			CircleShape shape(30.f);
			shape.setFillColor(Color::Red);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 205.f), (row * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 2) {
			CircleShape shape(30.f,3);
			shape.setFillColor(Color::Green);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 205.f), (row * 75.f + 12)));
			window->draw(shape);
		}
		if (gemtype == 3) {
			CircleShape shape(30.f, 4);
			shape.setFillColor(Color::Blue);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 205.f), (row * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 4) {
			CircleShape shape(30.f, 5);
			shape.setFillColor(Color::Yellow);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 205.f), (row * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 5) {
			CircleShape shape(30.f, 6);
			shape.setFillColor(Color::Cyan);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((column * 75.f + 205.f), (row * 75.f + 5)));
			window->draw(shape);
		}
	}
	void setwindow(RenderWindow& window) {this->window = &window;}
	// this function covers the gem


};