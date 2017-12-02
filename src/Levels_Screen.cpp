//
// Created by Yiyang Zhao on 01/12/2017.
//

#include "Levels_Screen.hpp"




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
        item_box[i] = level[i].getGlobalBounds();
        window.draw(level[i]);
    }
    window.draw(title);
}

bool Levels_Screen :: check_clicked(sf::Vector2f mousePos, int selected_level, sf::RenderWindow &window)
{
    sf::FloatRect item_box = level[selected_level-1].getGlobalBounds();
    if(item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x)
    {
        level[selected_level-1].setFillColor(sf::Color::Red);
        draw((window));
        //window.draw(desired_option);
        window.display();
        return true;
    }
    else
        return false;

}

BoardState* Levels_Screen::get_Board() {
    return this->board;
}


int Levels_Screen :: run(sf::RenderWindow &window)

{
    sf:: Event Event;
    bool running = true;


    this->board = BoardStateLoader::loadBoardState(LEVEL_01);
    while(running)
    {

        while (window.pollEvent(Event))
        {

            if(Event.type == sf::Event::Closed)
            {
                running = false;
                return -1;
            }

            // return 2;

            if(Event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    return 1;
            }


        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));


            if (Levels_Screen::check_clicked(mousePosition, 1, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_TEST);
                return 2;
            }

            if (Levels_Screen::check_clicked(mousePosition, 2, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_01);
                return 2;
            }

            if (Levels_Screen::check_clicked(mousePosition, 3, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_TEST);
                return 2;
            }

            if (Levels_Screen::check_clicked(mousePosition, 4, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_TEST);
                return 2;
            }

            if (Levels_Screen::check_clicked(mousePosition, 5, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_01);
                return 2;
            }

            if (Levels_Screen::check_clicked(mousePosition, 6, window))
            {
                this->board = BoardStateLoader::loadBoardState(LEVEL_TEST);
                return 2;
            }


        }


        window.clear(sf::Color(40,140,240));
        draw(window);
        window.display();

    }
    return 1;

}