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
    window.setFramerateLimit(60);
    RectangleShape rect(Vector2f(75.f, 75.f));
    Color test(127, 255, 212);
    rect.setFillColor(test);
    rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(5.f);
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
        //ment to draw a 8x8 grid of squares on the right side of the window
        for (float i = 0; i < 8; i++) {
            for (float j = 0; j < 8; j++) {
                rect.setPosition(Vector2f((i*75.f + 200.f), (j*75.f)));
                window.draw(rect);
            }
        }
		board.drawgameboard();
        window.display();
    }

    return 0;
}