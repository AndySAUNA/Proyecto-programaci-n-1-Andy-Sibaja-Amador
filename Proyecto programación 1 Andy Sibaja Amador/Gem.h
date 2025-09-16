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
	int x, y;
	int gemtype;

public:
	Gem() {
		gemtype = 0;
		x = 0;
		y = 0;
		window = nullptr;
	}

	void setx(int x) { this->y = x; }
	void sety(int y) { this->x = y; }
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
			shape.setPosition(Vector2f((y * 75.f + 200.f), (x * 75.f)));
			window->draw(shape);
		}
		if (gemtype == 1) {
			CircleShape shape(30.f);
			shape.setFillColor(Color::Red);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((y * 75.f + 205.f), (x * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 2) {
			CircleShape shape(30.f,3);
			shape.setFillColor(Color::Green);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((y * 75.f + 205.f), (x * 75.f + 12)));
			window->draw(shape);
		}
		if (gemtype == 3) {
			CircleShape shape(30.f, 4);
			shape.setFillColor(Color::Blue);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((y * 75.f + 205.f), (x * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 4) {
			CircleShape shape(30.f, 5);
			shape.setFillColor(Color::Yellow);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((y * 75.f + 205.f), (x * 75.f + 5)));
			window->draw(shape);
		}
		if (gemtype == 5) {
			CircleShape shape(30.f, 6);
			shape.setFillColor(Color::Cyan);
			shape.setOutlineColor(Color::Black);
			shape.setOutlineThickness(5.f);
			shape.setPosition(Vector2f((y * 75.f + 205.f), (x * 75.f + 5)));
			window->draw(shape);
		}
	}
	void setwindow(RenderWindow& window) {this->window = &window;}
	// this function covers the gem


};