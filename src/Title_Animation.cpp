#include "Title_Animation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/**Draws the Clear animation at the start, and the tagline*/
int Title_Animation::run() {
    sf::IntRect rectSource(0,0,396,134);
    sf::Texture titleSequence;
    titleSequence.loadFromFile(TITLE_TEXTUREMAP);
    sf::Sprite sprite(titleSequence, rectSource);
    sprite.setOrigin(198,67);
    sprite.setPosition(window->getSize().x/2,window->getSize().y/2);
    rectSource.left = 0;
    rectSource.top = 0;
    sprite.setTextureRect(rectSource);
    
    load_font(REGULARFONT_FILEPATH);
    tagline = make_text(TAG_LINE, 40, 0, -100);
    
    clear_window();
    window->draw(sprite);
    window->draw(tagline);
    window->display();

    sf::Clock clock;
    frame_count = 0;
    waited = false;
    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            else if (Event.type == sf::Event::KeyPressed) {return SCREEN_MAINMENU;}
        }
        if (!waited && clock.getElapsedTime().asSeconds() > 1) {waited = true;}
        else if (frame_count <= 18) {
            if (waited && clock.getElapsedTime().asSeconds()>0.1f) {
                clock.restart();
                frame_count++;
                if (rectSource.left == 396) {
                    rectSource.left = 0;
                    rectSource.top += 134;
                } else {rectSource.left += 396;}
                sprite.setTextureRect(rectSource);
                clear_window();
                window->draw(sprite);
                window->draw(tagline);
            }
            window->display();
        } else {return SCREEN_MAINMENU;}
    }
}
