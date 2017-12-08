#ifndef CLEAR_TITLE_ANIMATION_HPP
#define CLEAR_TITLE_ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "Screen_Abstract.hpp"

class Title_Animation : public Screen_Abstract {
    public:
        int draw_sprite();
        int draw_tagline();
        int run();
};

#endif //CLEAR_TITLE_ANIMATION_HPP
