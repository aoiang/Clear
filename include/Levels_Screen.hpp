//
// Created by Yiyang Zhao on 01/12/2017.
//

#ifndef CSCI437_LEVELS_SCREEN_HPP
#define CSCI437_LEVELS_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen_Abstract.hpp"
#include <string>
#include "GameLogic.hpp"
#include "GameView_Screen.hpp"
#include "BoardStateLoader.hpp"

class Levels_Screen : public GameView_Screen{
    private:
        sf::Text level[20];
        sf::FloatRect item_box[20];
        BoardState * board;


    public:
        void draw(sf::RenderWindow &window);
        bool check_clicked(sf::Vector2f mousePos, int selected_level, sf::RenderWindow &window);
        int run(sf::RenderWindow &window);
        BoardState* get_Board();


};


#endif //CSCI437_LEVELS_SCREEN_HPP
