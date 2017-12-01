#include "Title_Animation.hpp"
#include <SFML/Graphics.hpp>

/**Draws the clear animation at the start  */
int Title_Animation::draw_sprite(sf::RenderWindow &window)
{
    sf:: Event Event;
    window.clear(sf::Color(40,140,240));

    int count=0;
    sf::Clock clock;

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

        if (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return -1;}
            else if (Event.type == sf::Event::KeyPressed) {return 1;}
        }

        if (rectSource.top==0 && rectSource.left ==0) {sleep(sf::seconds(0.5));}
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
int Title_Animation::draw_tagline(sf::RenderWindow &window)
{
    sf:: Event Event;
    window.clear(sf::Color(40,140,240));

    int fontSize = 50;
    int count = 0;

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
        if (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return -1;}
            else if (Event.type == sf::Event::KeyPressed) {return 1;}
        }
        if (clock.getElapsedTime().asSeconds()>0.25f && count<15) //&& count<18)
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
int Title_Animation::run(sf::RenderWindow &window)
{
    sf:: Event Event;
    bool running = true;
    while(running)
    {

        while (window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                    running = false;
                    return -1;
            }

        }
        draw_sprite(window);
        int next_screen = draw_tagline(window);
        window.display();
        return next_screen;
    }
    return 1;
}
