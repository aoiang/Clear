#include "Levels_Screen.hpp"

/**Draws each level, mark red to unaccessible level*/
void Levels_Screen::draw(sf::RenderWindow &window)
{
    unsigned int fontSize = 36;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if(!font.loadFromFile(REGULARFONT_FILEPATH))
    {
        sf::CircleShape circle;
        circle.setRadius(20);
        window.draw(circle);

    }
    sf::Text title("Levels", font, 100);
    sf::FloatRect titlebox;
    titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)-260));

    for (int i = 0; i < LEVELS; i++){
        std::string str_level = std::to_string(i+1);
        level[i] = sf::Text(sf::String(str_level), font, fontSize);
        item_box[i] = level[i].getGlobalBounds();

        level[i].setOrigin(item_box[i].width/3.0f, item_box[0].height/3.0f);
        level[i].setPosition(sf::Vector2f((window.getSize().x/6) + (i % 5) * 100, (window.getSize().y/3) + i / 5 * 100));
        if(i >= finished_level){
            level[i].setFillColor(sf::Color::Red);
        }
        item_box[i] = level[i].getGlobalBounds();
        window.draw(level[i]);
    }
    window.draw(title);
}

/**check when mouse is clicked*/
bool Levels_Screen :: check_clicked(sf::Vector2f mousePos, int selected_level, sf::RenderWindow &window)
{
    sf::FloatRect item_box = level[selected_level-1].getGlobalBounds();
    if(item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x)
    {
        level[selected_level-1].setFillColor(sf::Color::Red);
        draw(window);
        window.display();
        return true;
    }
    else
        return false;

}


/**inialize all parameters & run the levels screen*/
int *Levels_Screen :: run(sf::RenderWindow &window, int curr_level)

{
    sf:: Event Event;
    bool running = true;
    int *re = new int[2];
    re[0] = 0;
    re[1] = curr_level;
    if(curr_level >= finished_level){
        finished_level = curr_level;
    }

    while(running)
    {

        while (window.pollEvent(Event))
        {

            if(Event.type == sf::Event::Closed)
            {
                running = false;
                re[0] = -1;
                return re;
            }

            if(Event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    re[0] = 1;
                    return re;
            }
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));


            for (int lv = 0; lv < 6; lv ++){
                if (Levels_Screen::check_clicked(mousePosition, lv+1, window) && level[lv].getFillColor() != sf::Color::Red)
                {
                    re[0] = 2;
                    re[1] = lv+1;
                    return re;
                }
            }


        }
        window.clear(sf::Color(40,140,240));
        draw(window);
        window.display();

    }


}
