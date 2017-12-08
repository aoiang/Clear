#ifndef CSCI437_LEVELS_SCREEN_HPP
#define CSCI437_LEVELS_SCREEN_HPP

#include "Screen_Abstract.hpp"
#include "GameLogic.hpp"
#include "GameView_Screen.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Levels_Screen : public GameView_Screen{
    private:
        sf::Text level[LEVELS];
        sf::Text title;
    public:
        void draw();
        int run();
};


#endif //CSCI437_LEVELS_SCREEN_HPP
