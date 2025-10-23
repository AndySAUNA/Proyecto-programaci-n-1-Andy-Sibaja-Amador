#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
#include "Game.h"
class Menu
{
private:
	Font font;
	bool gameactive;
	bool menuactive;
	RenderWindow* windows;
	Game* G;
public:
	Menu();
	void gamemenu(int x,int y);
	void Gameloop();
	void draw_Menu();

};

