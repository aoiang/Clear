#ifndef CLEAR_TITLE_ANIMATION_HPP
#define CLEAR_TITLE_ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "Screen_Abstract.hpp"
#include "Definitions.hpp"

class Title_Animation : public Screen_Abstract {
    private:
        sf::Text tagline;
        int frame_count;
        bool waited;
    public:
        int run();
};

#endif //CLEAR_TITLE_ANIMATION_HPP
