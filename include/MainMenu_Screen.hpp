#ifndef CLEAR_MAINMENU_SCREEN_HPP
#define CLEAR_MAINMENU_SCREEN_HPP

#define MAX_NUM_OF_ITEMS 3
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen_Abstract.hpp"

class MainMenu_Screen : public Screen_Abstract
{
    private:
       // sf::Text title;
        sf::Text * menuItem_0;
       // sf::Text * menuItem_1;
       // sf::Text * menuItem_2;
        sf::FloatRect  item_0_box;
        sf::FloatRect  item_1_box;
        sf::FloatRect  item_2_box;
    public:
        void draw(sf::RenderWindow &window);
        bool check_clicked(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window);
        int getSelectedOption(sf::RenderWindow &window);
        int run(sf::RenderWindow &window);
};

#endif //CLEAR_MAINMENU_SCREEN_HPP
