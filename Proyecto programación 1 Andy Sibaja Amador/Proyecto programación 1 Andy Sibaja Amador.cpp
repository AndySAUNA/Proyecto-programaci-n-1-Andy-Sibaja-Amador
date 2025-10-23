#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
using namespace std;
#include <iostream>
#include "Gameboard.h"
#include "Game.h"
#include "menu.h"

int main()
{
    Menu men;
    men.Gameloop();

    return 0;
}

//delay function for debugging
//std::this_thread::sleep_for(chrono::milliseconds(500));
//system("cls"); for clearing console