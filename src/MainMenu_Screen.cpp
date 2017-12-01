#include "MainMenu_Screen.hpp"
#include "Title_Animation.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>



void MainMenu_Screen:: draw(sf::RenderWindow &window)
{
    int fontSize = 50;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if(!font.loadFromFile(REGULARFONT_FILEPATH))
    {
       sf::CircleShape circle;
       circle.setRadius(20);
       window.draw(circle);

    }
    sf::Text title(GAME_TITLE, font, fontSize);
    sf::FloatRect titlebox;
    titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window.getSize().x/2,window.getSize().y/2));

    
    this->menuItem_0 = new sf::Text(MAINMENUITEM_0, font, fontSize);
    //sf::FloatRect item_0_box;
    item_0_box = menuItem_0->getGlobalBounds();

    menuItem_0->setOrigin(item_0_box.width/2.0f,item_0_box.height/2.0f);
    menuItem_0->setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)+50));
    item_0_box = menuItem_0->getGlobalBounds();

    sf::Text menuItem_1(MAINMENUITEM_1, font, fontSize);
    //sf::FloatRect item_1_box;
    item_1_box = menuItem_1.getGlobalBounds();
    menuItem_1.setOrigin(item_1_box.width/2.0f,item_1_box.height/2.0f);
    menuItem_1.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)+100));


    sf::Text menuItem_2(MAINMENUITEM_2, font, fontSize);
    sf::FloatRect item_2_box;
    item_2_box = menuItem_2.getGlobalBounds();
    menuItem_2.setOrigin(item_2_box.width/2.0f,item_2_box.height/2.0f);
    menuItem_2.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)+150));

    window.draw(*(menuItem_0));
    window.draw(menuItem_1);
    window.draw(menuItem_2);
    window.draw(title);

}
bool MainMenu_Screen :: check_clicked(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window)
{
    sf::FloatRect item_box = desired_option.getGlobalBounds();
    if(item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x)
    {
        desired_option.setFillColor(sf::Color::Red);         
        draw((window));
        //window.display();
        return true;
    }
    else
        return false;
    
}
int MainMenu_Screen :: getSelectedOption(sf::RenderWindow &window)
{
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      //  item_0_box = 
        //sf::Vector2f mpFloat = static_cast<sf::FloatRect>((mousePosition));
        //sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
        //sf::Vector2f pixlePosition = mousePosition.mapCoordsToPixel(static_cast<sf::FloatRect>(sf::Mouse::getPosition(window)));
       /*if(item_0_box.top < mousePosition.y && (item_0_box->top + item_0_box->height) > mousePosition.y && item_0_box->left < mousePosition.x && (item_0_box->left + item_0_box->width) > mousePosition.x)
        {
           
           return 2;
            
        }
        else
            return -1;*/
}
int MainMenu_Screen :: run(sf::RenderWindow &window)


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

           // return 2;
            
            if(Event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    return 2;
            }


        }
         if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                if (check_clicked(mousePosition, *menuItem_0, window))
                {
                        return 2;
                }
            }
        window.clear(sf::Color(40,140,240));
        draw(window);
        window.display();

    }
   return 1;

}
