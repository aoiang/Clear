#ifndef CLEAR_TITLE_ANIMATION_HPP
#define CLEAR_TITLE_ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "Screen_Abstract.hpp"

class Title_Animation : public Screen_Abstract{
    public:
        int draw_sprite(sf::RenderWindow &window);
        int draw_tagline(sf::RenderWindow &window);
        int *run(sf::RenderWindow &window);
};

#endif //CLEAR_TITLE_ANIMATION_HPP
