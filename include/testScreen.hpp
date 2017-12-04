#ifndef TESTSCREEN_HPP
#define TESTSCREEN_HPP
#include <SFML/Graphics.hpp>
#include "Screen_Abstract.hpp"
class testScreen : public Screen_Abstract
{
    public:
        void set_item_position(sf::Text  item, int y, sf::RenderWindow &window);
        int run(sf::RenderWindow &window);

};

#endif
