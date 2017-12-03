#ifndef CLEAR_MAINMENU_SCREEN_HPP
#define CLEAR_MAINMENU_SCREEN_HPP

#define MAX_NUM_OF_ITEMS 3
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen_Abstract.hpp"
#include "BoardState.hpp"

class MainMenu_Screen : public Screen_Abstract
{
    private:
        sf::Text * title;
        sf::Text * menuItems;
    public:
        void draw(sf::RenderWindow &window);
        bool check_mousover(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window);
        void set_item_position(sf::Text*, int, sf::RenderWindow&);
        int getSelectedOption(sf::RenderWindow &window);
        int *run(sf::RenderWindow &window, int curr_level);

};

#endif //CLEAR_MAINMENU_SCREEN_HPP
