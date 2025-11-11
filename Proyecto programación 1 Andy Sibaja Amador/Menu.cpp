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
        if (G == nullptr) { throw 2; }
        if (G->endgamer() == false) {
            if (x > 90 && x < (90 + 220) && y > 190 && y < (190 + 50)) { G->reset_game(); G->setgameactive(true); }
            if (x > 90 && x < (90 + 230) && y > 290 && y < (290 + 50)) { G->reset_game(); G->icegame(); G->setgameactive(true); }
            if (x > 90 && x < (90 + 230) && y > 390 && y < (390 + 50)) { G->reset_game(); G->fast_game(); G->setgameactive(true); }
        }
        else {
            if (x > 90 && x < (90 + 220) && y > 190 && y < (190 + 50)) { G->reset_game(); G->setgameactive(true); }
        }
    }
    
    catch (int error) {
        if (error == 1) { cout << "error in game menu: window pointer is null" << endl; }
        if (error == 2) { cout << "error in game menu: game pointer is null" << endl; }
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
        // assuming if game isn't active, then either we have menu or end menu based if end game is active
        if (G->getgameactive() == false) {
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
        if (G->getgameactive() == true){
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
        if (G->getgameactive() == true) {
            game.drawgame();
        }
        else if (G->endgamer() == true) {
            draw_end();
        }
        else {
            draw_Menu();
        }
        window.display();
    }
}

void Menu::draw_Menu()
{
    windows->clear(Color::Blue);
    //writes welcome
    Text text1;
    text1.setFont(font);
    text1.setString("Welcome!");
    text1.setCharacterSize(24);
    text1.setFillColor(Color::White);
    text1.setPosition(100.f, 100.f);
    windows->draw(text1);
    //draws square for normal game button
    RectangleShape rect2(Vector2f(220.f, 50.f));
    rect2.setFillColor(Color::Black);
    rect2.setOutlineColor(Color::Red);
    rect2.setOutlineThickness(5.f);
    rect2.setPosition(Vector2f((100 - 10), (200 - 10)));
    windows->draw(rect2);
    //writes play normal game
    Text text2;
    text2.setFont(font);
    text2.setString("Play normal Game");
    text2.setCharacterSize(24);
    text2.setFillColor(Color::White);
    text2.setPosition(100.f, 200.f);
    windows->draw(text2);
    //draws square for ice game button
    RectangleShape rect3(Vector2f(230.f, 50.f));
    rect3.setFillColor(Color::Black);
    rect3.setOutlineColor(Color::Red);
    rect3.setOutlineThickness(5.f);
    rect3.setPosition(Vector2f((100 - 10), (300 - 10)));
    windows->draw(rect3);
    // writes play game with ice
    Text text3;
    text3.setFont(font);
    text3.setString("Play Game with Ice!");
    text3.setCharacterSize(24);
    text3.setFillColor(Color::White);
    text3.setPosition(100.f, 300.f);
    windows->draw(text3);
    //draws square for ice game button
    RectangleShape rect4(Vector2f(230.f, 50.f));
    rect4.setFillColor(Color::Black);
    rect4.setOutlineColor(Color::Red);
    rect4.setOutlineThickness(5.f);
    rect4.setPosition(Vector2f((100 - 10), (400 - 10)));
    windows->draw(rect4);
    // writes fast game
    Text text4;
    text4.setFont(font);
    text4.setString("Play Fast Game!");
    text4.setCharacterSize(24);
    text4.setFillColor(Color::White);
    text4.setPosition(100.f, 400.f);
    windows->draw(text4);

}

void Menu::draw_end()
{
    //writes welcome
    Text text1;
    text1.setFont(font);
    text1.setString("end of game!");
    text1.setCharacterSize(24);
    text1.setFillColor(Color::White);
    text1.setPosition(100.f, 100.f);
    windows->draw(text1);
    //draws square for normal game button
    RectangleShape rect1(Vector2f(220.f, 50.f));
    rect1.setFillColor(Color::Black);
    rect1.setOutlineColor(Color::Red);
    rect1.setOutlineThickness(5.f);
    rect1.setPosition(Vector2f((100 - 10), (200 - 10)));
    windows->draw(rect1);
    //writes welcome
    Text text2;
    text2.setFont(font);
    text2.setString("score: " + G->getscore());
    text2.setCharacterSize(24);
    text2.setFillColor(Color::White);
    text2.setPosition(100.f, 200.f);
    windows->draw(text2);
    //draws square for normal game button
    RectangleShape rect2(Vector2f(220.f, 50.f));
    rect2.setFillColor(Color::Black);
    rect2.setOutlineColor(Color::Red);
    rect2.setOutlineThickness(5.f);
    rect2.setPosition(Vector2f((100 - 10), (200 - 10)));
    windows->draw(rect2);
}
