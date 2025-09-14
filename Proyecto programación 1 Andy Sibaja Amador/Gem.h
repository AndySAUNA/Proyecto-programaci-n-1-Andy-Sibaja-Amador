#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
#include <string>
#include <iostream>
#include <random>
using namespace std;


class Gem {
private:
	int positionx, positiony;
	int gemtype;

public:
	Gem(int positionx, int positiony) {
		srand((unsigned)time(0));
		this->positionx = positionx;
		this->positiony = positiony;
		gemtype = (rand() % 5)+1;
	}
	void setpositionx(int positionx) { this->positionx = positionx; }
	void setpositiony(int positiony) { this->positiony = positiony; }
	int getgemtype() { return gemtype; }
	// this function draws a gem based on its type and position;
	void draw(RenderWindow& window,int i, int j) {
		if (gemtype == 1) {
			CircleShape shape(30.f);
			shape.setFillColor(Color::Red);
			shape.setPosition(Vector2f((i * 75.f + 205.f), (j * 75.f + 5)));
			window.draw(shape);
		}
		if (gemtype == 2) {
			CircleShape shape(30.f,3);
			shape.setFillColor(Color::Green);
			shape.setPosition(Vector2f((i * 75.f + 205.f), (j * 75.f + 5)));
			window.draw(shape);
		}
		if (gemtype == 3) {
			CircleShape shape(30.f, 4);
			shape.setFillColor(Color::Blue);
			shape.setPosition(Vector2f((i * 75.f + 205.f), (j * 75.f + 5)));
			window.draw(shape);
		}
		if (gemtype == 4) {
			CircleShape shape(30.f, 5);
			shape.setFillColor(Color::Yellow);
			shape.setPosition(Vector2f((i * 75.f + 205.f), (j * 75.f + 5)));
			window.draw(shape);
		}
		if (gemtype == 5) {
			CircleShape shape(30.f, 6);
			shape.setFillColor(Color::Cyan);
			shape.setPosition(Vector2f((i * 75.f + 205.f), (j * 75.f + 5)));
			window.draw(shape);
		}
	}

};