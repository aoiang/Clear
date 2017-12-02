#ifndef CLEAR_SCREEN_ABSTRACT_HPP
#define CLEAR_SCREEN_ABSTRACT_HPP

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

class Screen_Abstract {
    public:
        virtual int run (sf::RenderWindow &window) = 0;
};

#endif //CLEAR_SCREEN_ABSTRACT_HPP
