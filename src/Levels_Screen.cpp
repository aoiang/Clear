#include "Levels_Screen.hpp"

/**Draws each level, mark red to unaccessible level*/
void Levels_Screen::draw(sf::RenderWindow &window) {
    window.clear(sf::Color(40,140,240));
    for (int i = 0; i < LEVELS; i++) {window.draw(level[i]);}
    window.draw(*title);
}

/**Sets GameLogic*/
void Levels_Screen::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

/**Check when mouse is over entry*/
bool Levels_Screen::check_mousover(sf::Vector2f mousePos, int selected_level, sf::RenderWindow &window) {
    sf::FloatRect item_box = level[selected_level-1].getGlobalBounds();
    if (item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x) {return true;}
    else {return false;}
}

/**Inialize all parameters & run the levels screen*/
int Levels_Screen::run(sf::RenderWindow &window) {
    unsigned int fontSize = 36;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if (!font.loadFromFile(REGULARFONT_FILEPATH)) {
        sf::CircleShape circle;
        circle.setRadius(20);
        window.draw(circle);
    }

    title = new sf::Text("Levels", font, 100);
    sf::FloatRect titlebox = title->getGlobalBounds();
    title->setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title->setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)-260));

    if (logic->get_max_level() <= 0) {logic->set_cur_level(1);}

    for (int i = 0; i < LEVELS; i++){
        std::string str_level = std::to_string(i+1);
        level[i] = sf::Text(sf::String(str_level), font, fontSize);
        sf::FloatRect tmp = level[i].getGlobalBounds();
        level[i].setOrigin(tmp.width/3.0f, tmp.height/3.0f);
        level[i].setPosition(sf::Vector2f((window.getSize().x/6) + (i % 5) * 100, (window.getSize().y/3) + i / 5 * 100));
        if (i >= logic->get_max_level()) {level[i].setFillColor(sf::Color(255, 255, 255, 120));}
        window.draw(level[i]);
    }

    sf:: Event Event;
    bool running = true;

    while(running) {
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if ((Event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {return SCREEN_MAINMENU;}
        }

        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int lv = 0; lv < LEVELS; lv ++) {
                if (Levels_Screen::check_mousover(mousePosition, lv+1, window) && lv < logic->get_max_level()) {
                    logic->set_cur_level(lv+1);
                    return SCREEN_GAMEVIEW;
                }
            }
        }

        for (int i=0; i < LEVELS; i++) {
            if (i < logic->get_max_level()) {level[i].setFillColor(sf::Color::White);}
            else {level[i].setFillColor(sf::Color(255, 255, 255, 120));}
            if (Levels_Screen::check_mousover(mousePosition, i+1, window) && i < logic->get_max_level()) {level[i].setFillColor(sf::Color(240, 100, 100));}
        }

        draw(window);
        window.display();
    }
}
