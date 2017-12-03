#include "Title_Animation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/**Draws the clear animation at the start  */
int Title_Animation :: draw_sprite(sf::RenderWindow &window)
{
    window.clear(sf::Color(40,140,240));

    int count=0;
    sf::Clock clock;
    sf::Event event;

    sf::IntRect rectSource(0,0,396,134);
    sf::Texture titleSequence;
    titleSequence.loadFromFile(TITLE_TEXTUREMAP);

    sf::Sprite sprite(titleSequence, rectSource);
    sprite.setOrigin(198,67);
    sprite.setPosition(window.getSize().x/2,window.getSize().y/2);

    while(count!=18)
    {
        window.draw(sprite);
        window.display();

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {return -1;}
            if(event.type == sf::Event::KeyPressed) {return 1;}
        }
        if(clock.getElapsedTime().asSeconds()>0.1f && count<18)
            {
                if(rectSource.left == 392)
                    {
                        rectSource.left = 0;
                        rectSource.top += 134;
                    }
                    else
                        rectSource.left += 392;

                    sprite.setTextureRect(rectSource);
                    clock.restart();
                    count++;
            }
    }
    return 1;
}

/**draws/fades in the tagline */
int Title_Animation :: draw_tagline(sf::RenderWindow &window)
{
    window.clear(sf::Color(40,140,240));

    int fontSize = 50;
    int count = 0;
    sf:: Event event;
    window.pollEvent(event);

    sf::FloatRect textbox;
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    sf::Text tagline(TAG_LINE, font, fontSize);
    tagline.setCharacterSize(50);
    textbox = tagline.getGlobalBounds();
    tagline.setOrigin(textbox.width/2.0f,textbox.height/2.0f);
    tagline.setPosition(window.getSize().x/2,window.getSize().y/2);
    tagline.setFillColor(sf::Color(255,255,255, 34));
    while(count!=15)
    {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {return -1;}
            if(event.type == sf::Event::KeyPressed) {return 1;}
        }

        if(clock.getElapsedTime().asSeconds()>0.25f && count<15) //&& count<18)
        {
            int hue = count*17;
            tagline.setFillColor(sf::Color(255,255,255,hue));
            clock.restart();
            count++;
            window.draw(tagline);
            window.display();
        }
    }
    return 1;
}

/**runs the opening screen */
int *Title_Animation :: run(sf::RenderWindow &window, int curr_level)
{
    int *re = new int[2];
    re[0] = 0;
    re[1] = curr_level;
    sf:: Event Event;
    bool running = true;
    while (running)
    {
        if (draw_sprite(window) == -1) {
            re[0] = -1;
            return re;
        }
        int next_screen = draw_tagline(window);
        re[0] = next_screen;
        return re;
    }
}
