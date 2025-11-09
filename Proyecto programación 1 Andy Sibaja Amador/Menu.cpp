#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("resources/fonts/OpenSans-Regular.ttf");
    gameactive = false;
    menuactive = true;
    windows = nullptr;
    G = nullptr;
}

void Menu::gamemenu(int x, int y)
{
    try {
        if (windows == nullptr) { throw 1; }
        windows->clear(Color::Blue);
        if (x > 90 && x < (90 + 220) && y > 190 && y < (190 + 50)) { menuactive = false; gameactive = true; }
        if (x > 90 && x < (90 + 230) && y > 290 && y < (290 + 50)) { G->icegame(); menuactive = false; gameactive = true; }
    }
    
    catch (int error) {
        if (error == 1) { cout << "error in game menu: window pointer is null" << endl; }
    }
}

void Menu::Gameloop()
{
    int row = 0, column = 0, rowclick, columnclick;
    bool mouseButtonPressed = false;
    RenderWindow window(VideoMode(800, 600), "Proyecto programación 1 Andy Sibaja");
    window.setFramerateLimit(60);

    windows = &window;
    Game game(window);
    G = &game;

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

        if (menuactive == true) {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed)
                {
                    std::cout << "Left mouse button clicked at: "
                        << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    columnclick = event.mouseButton.x;//column
                    rowclick = event.mouseButton.y;//row
                    gamemenu(columnclick,rowclick);
                    mouseButtonPressed = false;

                }
            }
        }
        if (gameactive == true){
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed)
                {
                    std::cout << "Left mouse button clicked at: "
                        << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    columnclick = event.mouseButton.x;//column
                    rowclick = event.mouseButton.y;//row
                    if (columnclick > 200) {
                        column = (columnclick - 200) / 75;
                        row = rowclick / 75;
                        cout << "posrc is:" << row << "," << column << endl;
                        game.select(row, column);
                    }
                    mouseButtonPressed = false; // Reset the flag

                }
            }
        }
        

        window.clear();
        if (gameactive == true) {
            game.drawgame();
        }
        if (menuactive == true) {
            draw_Menu();
        }
        window.display();
    }
}

void Menu::draw_Menu()
{
    //writes welcome
    Text text1;
    text1.setFont(font);
    text1.setString("Welcome!");
    text1.setCharacterSize(24);
    text1.setFillColor(Color::White);
    text1.setPosition(100.f, 100.f);
    windows->draw(text1);
    //draws square for normal game button
    RectangleShape rect(Vector2f(220.f, 50.f));
    rect.setFillColor(Color::Black);
    rect.setOutlineColor(Color::Red);
    rect.setOutlineThickness(5.f);
    rect.setPosition(Vector2f((100 - 10), (200 - 10)));
    windows->draw(rect);
    //writes play normal game
    Text text2;
    text2.setFont(font);
    text2.setString("Play normal Game");
    text2.setCharacterSize(24);
    text2.setFillColor(Color::White);
    text2.setPosition(100.f, 200.f);
    windows->draw(text2);
    //draws square for ice game button
    RectangleShape rect2(Vector2f(230.f, 50.f));
    rect2.setFillColor(Color::Black);
    rect2.setOutlineColor(Color::Red);
    rect2.setOutlineThickness(5.f);
    rect2.setPosition(Vector2f((100 - 10), (300 - 10)));
    windows->draw(rect2);
    // writes play game with ice
    Text text3;
    text3.setFont(font);
    text3.setString("Play Game with Ice!");
    text3.setCharacterSize(24);
    text3.setFillColor(Color::White);
    text3.setPosition(100.f, 300.f);
    windows->draw(text3);
}
