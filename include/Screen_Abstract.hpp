#ifndef SCREEN_ABSTRACT_HPP
#define SCREEN_ABSTRACT_HPP

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
class Screen_Abstract 
{
    public:
        virtual int run (sf::RenderWindow &window) = 0;

};
#endif
