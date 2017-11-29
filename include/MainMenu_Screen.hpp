
#define MAINMENU_SCREEN_HPP

#define MAX_NUM_OF_ITEMS 3
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen_Abstract.hpp"
class MainMenu_Screen : public Screen_Abstract
{
    public:
        void draw(sf::RenderWindow &window);
        int run(sf::RenderWindow &window);
};

