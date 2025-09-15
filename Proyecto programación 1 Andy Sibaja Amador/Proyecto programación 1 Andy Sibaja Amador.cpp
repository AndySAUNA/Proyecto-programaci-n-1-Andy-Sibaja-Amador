#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
using namespace std;
#include <iostream>
#include "Gem.h"
#include "Gameboard.h"

int main()
{
    RenderWindow window(VideoMode(800, 600), "Proyecto programación 1 Andy Sibaja");
    window.setFramerateLimit(1);
	Gameboard board(window);
	board.randomizegameboard();
	Gem** sboard = board.getboard();
	bool** solutionf = board.detectmatches(sboard);
    for (int i = 0; i < 8; i++) {
        cout << endl;
        for (int j = 0; j < 8; j++) {
            if (solutionf[i][j] == true) { cout << "(t)" << "\t"; }
            if (solutionf[i][j] == false) { cout << "f" << "\t"; }
        }
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "the left button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
        }

        window.clear();
		board.drawgameboard();
		board.deletematches();
        board.drawgameboard();
        window.display();
    }

    return 0;
}