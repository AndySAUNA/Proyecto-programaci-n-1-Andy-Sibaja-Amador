#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
using namespace std;
#include <iostream>
#include "Gem.h"
#include "Gameboard.h"
#include "Game.h"

int main()
{
    int x=0, y=0, sx, sy;
    bool mouseButtonPressed = false;
    RenderWindow window(VideoMode(800, 600), "Proyecto programación 1 Andy Sibaja");
    window.setFramerateLimit(60);

	Gameboard board(window);
	board.randomizegameboard();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //if (event.type == Event::MouseButtonPressed)
        //{
        //    if (event.mouseButton.button == sf::Mouse::Left)
        //    {
				
        //        std::cout << "the left button was pressed" << std::endl;
        //        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        //        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
        //        //x = event.mouseButton.x;
        //        //y = event.mouseButton.y;
        //    }
        //}
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) // Check for left mouse button
            {
                mouseButtonPressed = true;
            }
        }

        // Check for mouse button released event
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed)
            {
                std::cout << "Left mouse button clicked at: "
                    << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                x = event.mouseButton.x;
                y = event.mouseButton.y;
                if (x>200){
                    sx = (x - 200) / 75;
                    sy = y / 75;
                    cout << "posxy is:" << sx + 1 << "," << sy + 1 << endl;
                }
                mouseButtonPressed = false; // Reset the flag

            }
        }

        window.clear();
		board.drawgameboard();
        window.display();
    }

    return 0;
}

//delay function for debugging
//std::this_thread::sleep_for(std::chrono::milliseconds(500));