#include "MainMenu_Screen.hpp"
#include "Title_Animation.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**Draw menu items*/
void MainMenu_Screen::draw() {
    window->clear(sf::Color(40,140,240));
    for (int i=0; i<5; i++) {window->draw(menuItems[i]);}
    window->draw(title);
}

/**Sets menu item positions*/
void MainMenu_Screen::set_item_position(sf::Text * item, int y) {
    sf::FloatRect tmp = item->getGlobalBounds();
    item->setOrigin(tmp.width / 2.0f, tmp.height / 2.0f);
    item->setPosition(sf::Vector2f(window->getSize().x / 2, (window->getSize().y / 2) + y));
}

/**Inialize all parameters and run the main menu screen*/
int MainMenu_Screen::run() {
    std::string const options[] = {"New Game", "Continue", "Levels", "Infinite", "Custom"};
    load_font(REGULARFONT_FILEPATH);
    
    title = sf::Text(GAME_TITLE, font, 150);
    set_item_position(&title, -200);
    
    for (int i=0; i<menu_items_count; i++) {
        menuItems[i] = sf::Text(options[i], font, 50);
        set_item_position(&menuItems[i], i*50);
    }
    
    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (is_mouse_over_text(menuItems[0])) { //new game
                logic->set_cur_level(1);
                return SCREEN_TRANSITION;
            }
            else if (is_mouse_over_text(menuItems[1])) {return SCREEN_GAMEVIEW;}
            else if (is_mouse_over_text(menuItems[2])) {return SCREEN_LEVELSELECT;}
            else if (is_mouse_over_text(menuItems[3])) {return SCREEN_INFINITE;}
            else if (is_mouse_over_text(menuItems[4])) {return SCREEN_CUSTOM;}
        }
        
        for (int i=0; i<5; i++) {
            if (is_mouse_over_text(menuItems[i])) {menuItems[i].setFillColor(sf::Color(240, 100, 100));}
            else {menuItems[i].setFillColor(sf::Color::White);}
        }
        draw();
        window->display();
    }
}
