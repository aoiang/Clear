#include "testScreen.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

void testScreen::set_item_position(sf::Text  item, int y, sf::RenderWindow &window) {
    sf::FloatRect tmp = item.getGlobalBounds();
    item.setOrigin(tmp.width / 2.0f, tmp.height / 2.0f);
    item.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + y));
}
int testScreen::run(sf::RenderWindow &window)
{
    sf:: Event Event;
    bool running = true;
    unsigned int fontSize = 30;
    sf::Text title;
    sf::Font handFont;
    handFont.loadFromFile(HANDWRITTENFONT_FILEPATH);
    title =  sf::Text("Clear", handFont, 50);
    sf::Text  menuItem_0 =  sf::Text("Play Story Mode", handFont, fontSize);
    sf::Text  menuItem_1 =  sf::Text("Continue Playing", handFont, fontSize);
    title.setFillColor(sf::Color::Black);
    menuItem_0.setFillColor(sf::Color::Black);
    menuItem_1.setFillColor(sf::Color::Black);
    title.setPosition(100,100);
    menuItem_0.setPosition(150,150);
    menuItem_1.setPosition(250,250);
    set_item_position(title, -200, window);
    set_item_position(menuItem_0, 0, window);
    set_item_position(menuItem_1, 50, window);
    
    sf::FloatRect tmp1 = title.getGlobalBounds();
    title.setOrigin(tmp1.width / 2.0f, tmp1.height / 2.0f);
    title.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2)-180));
    tmp1 = title.getGlobalBounds();
    
    sf::FloatRect tmp2 = menuItem_0.getGlobalBounds();
    menuItem_0.setOrigin(0, tmp2.height / 2.0f);
    menuItem_0.setPosition(sf::Vector2f(180 , (window.getSize().y / 2)-120));
    tmp2 = menuItem_0.getGlobalBounds();
    
    sf::FloatRect tmp3 = menuItem_1.getGlobalBounds();
    menuItem_1.setOrigin(0, tmp3.height / 2.0f);
    menuItem_1.setPosition(sf::Vector2f(180 , (window.getSize().y / 2)-60));
    tmp3 = menuItem_1.getGlobalBounds();
    
    
    sf::RectangleShape checkBox1;
    checkBox1.setSize(sf::Vector2f(30,30));
    checkBox1.setOutlineColor(sf::Color::Red);
    checkBox1.setOutlineThickness(3);
    checkBox1.setFillColor(sf::Color::Transparent);
    sf::FloatRect cb1tmp = checkBox1.getGlobalBounds();
    checkBox1.setPosition(tmp2.left -((cb1tmp.left + cb1tmp.width)+cb1tmp.width/4), (tmp2.top+tmp2.height) - (cb1tmp.height +cb1tmp.width/6));
   
    
    sf::RectangleShape checkBox2;
    checkBox2.setSize(sf::Vector2f(30,30));
    checkBox2.setOutlineColor(sf::Color::Red);
    checkBox2.setOutlineThickness(3);
    checkBox2.setFillColor(sf::Color::Transparent);
    sf::FloatRect cb2tmp = checkBox2.getGlobalBounds();
    checkBox2.setPosition(tmp3.left -((cb2tmp.left + cb2tmp.width)+cb2tmp.width/4), (tmp3.top+tmp3.height) - (cb2tmp.height +cb2tmp.width/6));
    sf::Texture background_texture;
    sf::Vector2u tSize;
    sf::Vector2u wSize;
    
    sf::Sprite backgroundImage;
    if(!background_texture.loadFromFile(MAINMENU_BACKGROUND))
    {
       sf::CircleShape circle;
       circle.setRadius(20);
       window.draw(circle);
    }
    backgroundImage.setTexture(background_texture);
    //backgroundImage.scale(1.2,1.2);
    sf::FloatRect tmp = backgroundImage.getGlobalBounds();
    backgroundImage.setOrigin(tmp.width / 2.0f, tmp.height / 2.0f);
    backgroundImage.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2)));
    tSize = background_texture.getSize();
    wSize = window.getSize();
    float scaleX = (float)wSize.x/tSize.x;
    float scaleY= (float)wSize.y/tSize.y;
    backgroundImage.setScale(scaleX, scaleY);
    backgroundImage.scale(1.2,1.2);
    
    //sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    
    
    
    
    //backgroundImage.setPosition(300,300);
    //background.setTexture(&background_texture);
    sf::RectangleShape line;
    sf::RectangleShape line2;
    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                running = false;
                return EXIT_GAME;
            }
        }
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::FloatRect item_box = menuItem_1.getGlobalBounds();
        sf::FloatRect item_box0 = menuItem_0.getGlobalBounds();
        float linelength = (cb2tmp.width + item_box.width)+(cb2tmp.width+cb2tmp.left); //- (cb2tmp.left-cb2tmp.width));
        float line2length = (cb1tmp.width + item_box0.width)+(cb2tmp.width+cb2tmp.left);
        if (item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x) {
            checkBox2.setFillColor(sf::Color::Green);
            //line = sf::RectangleShape(sf::Vector2f(linelength, 3));
            //line.rotate(180);
            //line.setFillColor(sf::Color::Red);
            //line.setOrigin(((cb2tmp.left +cb2tmp.width +item_box.left + item_box.width)+(item_box.left - (cb2tmp.left-cb2tmp.width)))/2, menuItem_1.getPosition().y - item_box.height/3);
            //line.setPosition(((cb2tmp.width + tmp3.width)/2)-cb2tmp.width/2, cb2tmp.height/2);
        }
        else{
            checkBox2.setFillColor(sf::Color::Transparent);
        }
        if  (item_box0.top < mousePos.y && (item_box0.top + item_box0.height) > mousePos.y && item_box0.left < mousePos.x && (item_box0.left + item_box0.width) > mousePos.x) {   
                checkBox1.setFillColor(sf::Color::Green);
                //line2 = sf::RectangleShape(sf::Vector2f(line2length,3));
                //line2.rotate(180);
                //line2.setFillColor(sf::Color::Red);
                //line2.setOrigin(((cb1tmp.left +cb1tmp.width +item_box0.left + item_box0.width)+(item_box0.left - (cb1tmp.left-cb1tmp.width)))/2, menuItem_0.getPosition().y - item_box0.height/3);
                //line2.setPosition(((cb1tmp.width + tmp2.width)/2)-cb1tmp.width/2, cb1tmp.height/2);
            }
        else {
            checkBox1.setFillColor(sf::Color::Transparent);
        }
         window.clear(sf::Color::White);
         window.draw(backgroundImage);
         window.draw(title);
         window.draw(menuItem_0);
         window.draw(menuItem_1);
         window.draw(checkBox1);
         window.draw(checkBox2);
         window.draw(line);
         window.draw(line2);
         
         window.display();
      
    }
    return 3;
    
}
