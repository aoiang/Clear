#include "MainMenu_Screen.hpp"
#include "Title_Animation.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**Draw menu items*/
void MainMenu_Screen::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(40,140,240));
    for (int i=0; i<5; i++) {
        window.draw(menuItems[i]);
    }
    window.draw(*title);
}

/**Check when mouse is over an sf::Text object*/
bool MainMenu_Screen::check_mousover(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window) {
    sf::FloatRect item_box = desired_option.getGlobalBounds();
    if (item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x) {return true;}
    else {return false;}
}

/**Sets GameLogic*/
void MainMenu_Screen::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

/**Sets menu item positions*/
void MainMenu_Screen::set_item_position(sf::Text * item, int y, sf::RenderWindow &window) {
    sf::FloatRect tmp = item->getGlobalBounds();
    item->setOrigin(tmp.width / 2.0f, tmp.height / 2.0f);
    item->setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + y));
}

/**Inialize all parameters and run the main menu screen*/
int MainMenu_Screen::run(sf::RenderWindow &window) {
    unsigned int fontSize = 50;

    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if(!font.loadFromFile(REGULARFONT_FILEPATH)) {
       sf::CircleShape circle;
       circle.setRadius(20);
       window.draw(circle);
    }

    menuItems = new sf::Text[5]();
    title = new sf::Text(GAME_TITLE, font, 150);

    sf::Text * menuItem_0 = new sf::Text(MAINMENUITEM_0, font, fontSize);
    sf::Text * menuItem_1 = new sf::Text(MAINMENUITEM_1, font, fontSize);
    sf::Text * menuItem_2 = new sf::Text(MAINMENUITEM_2, font, fontSize);
    sf::Text * menuItem_3 = new sf::Text(MAINMENUITEM_3, font, fontSize);
    sf::Text * menuItem_4 = new sf::Text(MAINMENUITEM_4, font, fontSize);

    set_item_position(title, -200, window);
    set_item_position(menuItem_0, 0, window);
    set_item_position(menuItem_1, 50, window);
    set_item_position(menuItem_2, 100, window);
    set_item_position(menuItem_3, 150, window);
    set_item_position(menuItem_4, 200, window);

    menuItems[0] = *menuItem_0;
    menuItems[1] = *menuItem_1;
    menuItems[2] = *menuItem_2;
    menuItems[3] = *menuItem_3;
    menuItems[4] = *menuItem_4;

    sf:: Event Event;
    bool running = true;
    
    sf::Music elevator_music; 
    if (!elevator_music.openFromFile(MUSIC_FILEPATH))
        return -1;
    elevator_music.play();
    elevator_music.setLoop(true);

    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {return EXIT_GAME;}
        }

        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (check_mousover(mousePosition, menuItems[0], window)) { //new game
                logic->set_cur_level(1);
                return SCREEN_TRANSITION;
            } else if (check_mousover(mousePosition, menuItems[1], window)) { //continue
                return SCREEN_GAMEVIEW;
            } else if (check_mousover(mousePosition, menuItems[2], window)) { //level selection
                return SCREEN_LEVELSELECT;
            } else if (check_mousover(mousePosition, menuItems[3], window)) { //infinite mode
                return SCREEN_INFINITE;
            } else if (check_mousover(mousePosition, menuItems[4], window)) {} //settings
        }

        for (int i = 0; i < 5; i++) {
            if (check_mousover(mousePosition, menuItems[i], window)) {menuItems[i].setFillColor(sf::Color(240, 100, 100));}
            else {menuItems[i].setFillColor(sf::Color::White);}
        }

        draw(window);
        window.display();
    }
}
