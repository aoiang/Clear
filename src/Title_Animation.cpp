#include "Title_Animation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/**Draws the Clear animation at the start*/
int Title_Animation::draw_sprite(sf::RenderWindow &window) {
    window.clear(sf::Color(40,140,240));

    sf::Clock clock;
    sf::Event event;
    int frame_count = 0;

    sf::IntRect rectSource(0,0,396,134);
    sf::Texture titleSequence;
    titleSequence.loadFromFile(TITLE_TEXTUREMAP);

    sf::Sprite sprite(titleSequence, rectSource);
    sprite.setOrigin(198,67);
    sprite.setPosition(window.getSize().x/2,window.getSize().y/2);

    while(frame_count <= 18) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {return -1;}
            if(event.type == sf::Event::KeyPressed) {return 1;}
        }

        if (clock.getElapsedTime().asSeconds()>0.1f) {
            if (rectSource.left == 396) {
                rectSource.left = 0;
                rectSource.top += 134;
            } else {
                rectSource.left += 396;
            }

            sprite.setTextureRect(rectSource);
            clock.restart();
            frame_count++;

            window.clear(sf::Color(40,140,240));
            window.draw(sprite);
            window.display();
        }
    }
    return 1;
}

/**draws/fades in the tagline */
int Title_Animation::draw_tagline(sf::RenderWindow &window) {
    int frame_count = 0;
    sf:: Event event;
    sf::Clock clock;

    int fontSize = 50;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    sf::Text tagline(TAG_LINE, font, fontSize);
    tagline.setCharacterSize(fontSize);

    sf::FloatRect textbox;
    textbox = tagline.getGlobalBounds();

    tagline.setOrigin(textbox.width / 2.0f, textbox.height / 2.0f);
    tagline.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    tagline.setFillColor(sf::Color(255, 255, 255, 0));

    while (frame_count <= 255) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {return -1;}
            if(event.type == sf::Event::KeyPressed) {return 1;}
        }
        if(clock.getElapsedTime().asSeconds() > 0.01f) {
            window.clear(sf::Color(40,140,240));
            tagline.setFillColor(sf::Color(255, 255, 255, frame_count));
            clock.restart();
            frame_count++;
            window.draw(tagline);
            window.display();
        }
    }
    return 1;
}

/**runs the opening screen */
int Title_Animation::run(sf::RenderWindow &window) {
    if (draw_sprite(window) == -1) {return EXIT_GAME;}
    return draw_tagline(window);
}
