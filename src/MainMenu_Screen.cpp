#include "MainMenu_Screen.hpp"
#include "Title_Animation.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**Draw menu items*/
void MainMenu_Screen::draw() {
    clear_window();
    
    sf::Color color;
    for (int i=0; i<5; i++) {
        if (is_mouse_over_text(menuItems[i])) {color = sf::Color(240, 100, 100);}
        else {color = sf::Color::White;}
        menuItems[i].setFillColor(color);
    }
    
    for (int i=0; i<5; i++) {window->draw(menuItems[i]);}
    window->draw(title);
    window->display();
}

/**Inialize all parameters and run the main menu screen*/
int MainMenu_Screen::run() {
    std::string const options[] = {"New Game", "Continue", "Levels", "Infinite", "Custom"};
    load_font(REGULARFONT_FILEPATH);
    
    title = make_text(GAME_TITLE, 150, 0, 200);
    
    for (int i=0; i<menu_items_count; i++) {
        menuItems[i] = make_text(options[i], 50, 0, -1*(i*50));
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
        draw();
    }
}
