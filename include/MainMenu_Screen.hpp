#ifndef CLEAR_MAINMENU_SCREEN_HPP
#define CLEAR_MAINMENU_SCREEN_HPP

#define MAX_NUM_OF_ITEMS 3

#include "Screen_Abstract.hpp"
#include "BoardState.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu_Screen : public Screen_Abstract
{
    private:
        sf::Text * title;
        sf::Text * menuItems;
        GameLogic * logic;
    public:
        void draw(sf::RenderWindow&);
        bool check_mousover(sf::Vector2f, sf::Text, sf::RenderWindow&);
        void set_item_position(sf::Text*, int, sf::RenderWindow&);
        int getSelectedOption(sf::RenderWindow&);
        int *run(sf::RenderWindow&, int);
        void set_GameLogic(GameLogic&);
};

#endif //CLEAR_MAINMENU_SCREEN_HPP
