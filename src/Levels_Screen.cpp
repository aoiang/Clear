#include "Levels_Screen.hpp"

/**Draws each level*/
void Levels_Screen::draw() {
    window->clear(sf::Color(40,140,240));
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
}

/**Inialize all parameters & run the levels screen*/
int Levels_Screen::run() {
    load_font(REGULARFONT_FILEPATH);
    
    title = sf::Text("Levels", font, 100);
    sf::FloatRect titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window->getSize().x/2,(window->getSize().y/2)-260));

    for (int i=0; i<LEVELS; i++) {
        level[i] = sf::Text(sf::String(std::to_string(i+1)), font, 36);
        sf::FloatRect tmp = level[i].getGlobalBounds();
        level[i].setOrigin(tmp.width/3.0f, tmp.height/3.0f);
        level[i].setPosition(sf::Vector2f((window->getSize().x/6) + (i%5)*100, (window->getSize().y/3) + i / 5 * 100));
    }

    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {return SCREEN_MAINMENU;}
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i=0; i<LEVELS; i++) {
                if (i < logic->get_max_level() && Levels_Screen::is_mouse_over(level[i].getGlobalBounds())) {
                    logic->set_cur_level(i+1);
                    return SCREEN_GAMEVIEW;
                }
            }
        }
        draw();
        window->display();
    }
}
