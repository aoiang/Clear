#include "Levels_Screen.hpp"

/**Draws each level*/
void Levels_Screen::draw() {
    clear_window();
    window->draw(title);
    
    sf::Color color;
    for (int i=0; i<LEVELS; i++) {
        if (i < logic->get_max_level()) {
            if (Levels_Screen::is_mouse_over(level[i].getGlobalBounds())) {color = sf::Color(240, 100, 100);}
            else {color = sf::Color::White;}
        } else {color = sf::Color(255, 255, 255, 90);}
        level[i].setFillColor(color);
        window->draw(level[i]);
    }
    window->display();
}

/**Inialize all parameters & run the levels screen*/
int Levels_Screen::run() {
    load_font(REGULARFONT_FILEPATH);
    
    title = make_title("Levels");
    
    for (int i=0; i<LEVELS; i++) {
        level[i] = make_text(std::to_string(i+1), 36, 100*(i%5 - 2), -100*(i/5 - 1));
    }
    
    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {return SCREEN_MAINMENU;}
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i=0; i<LEVELS; i++) {
                if (i < logic->get_max_level() && Levels_Screen::is_mouse_over_text(level[i])) {
                    logic->set_cur_level(i+1);
                    return SCREEN_GAMEVIEW;
                }
            }
        }
        draw();
    }
}
