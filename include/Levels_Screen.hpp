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
        sf::Text level[20];
        sf::FloatRect item_box[20];
        GameLogic * logic;
    public:
        void draw(sf::RenderWindow&);
        bool check_clicked(sf::Vector2f mousePos, int selected_level, sf::RenderWindow &window);
        int run(sf::RenderWindow &window);
        void set_GameLogic(GameLogic&);
};


#endif //CSCI437_LEVELS_SCREEN_HPP
