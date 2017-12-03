//
// Created by Yiyang Zhao on 03/12/2017.
//

#ifndef CSCI437_INFINITE_SCREEN_HPP
#define CSCI437_INFINITE_SCREEN_HPP
#include "Screen_Abstract.hpp"
#include "GameLogic.hpp"
#include "GameView_Screen.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Infinite_Screen : public Screen_Abstract{
    private:
        sf::Text button[10];
        sf::FloatRect  item_box[10];
        sf::Text block_num[5];
        sf::Text start;
        int num_of_blocks[5];
        GameLogic * logic;

public:
        void init();
        void set(sf::RenderWindow &window);
        int block_size = 50;
        void draw(sf::RenderWindow &window);
        bool check_clicked(sf::Vector2f mousePos, int cur_button, sf::RenderWindow &window);
        bool start_clicked(sf::Vector2f mousePos, sf::RenderWindow &window);
        int *run(sf::RenderWindow &window, int curr_level);
        void set_GameLogic(GameLogic&);




};

#endif //CSCI437_INFINITE_SCREEN_HPP
