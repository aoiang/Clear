#ifndef CLEAR_MAINMENU_SCREEN_HPP
#define CLEAR_MAINMENU_SCREEN_HPP

#define MAX_NUM_OF_ITEMS 3

#include "Screen_Abstract.hpp"
#include "BoardState.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu_Screen : public Screen_Abstract {
    private:
        sf::Text title;
        static const int menu_items_count = 4;
        sf::Text menuItems[menu_items_count];
        static std::string const options[];
    public:
        void draw();
        int run();
};

#endif //CLEAR_MAINMENU_SCREEN_HPP
