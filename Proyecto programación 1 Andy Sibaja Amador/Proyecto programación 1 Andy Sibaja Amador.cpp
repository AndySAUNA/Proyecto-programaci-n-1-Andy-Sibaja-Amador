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
    int row=0, column=0, rowclick, columnclick;
    bool mouseButtonPressed = false;
    RenderWindow window(VideoMode(800, 600), "Proyecto programación 1 Andy Sibaja");
    window.setFramerateLimit(60);

	Gameboard board(window);
	board.randomizegameboard();
	Game game(window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
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
                columnclick = event.mouseButton.x;//column
                rowclick = event.mouseButton.y;//row
                if (columnclick>200){
                    column = (columnclick - 200) / 75;
                    row = rowclick / 75;
                    cout << "posrc is:" << row << "," << column << endl;
                    game.select(row, column);
                }
                mouseButtonPressed = false; // Reset the flag

            }
        }

        window.clear();
		game.drawgame();
        window.display();
    }

    return 0;
}

//delay function for debugging
//std::this_thread::sleep_for(chrono::milliseconds(500));