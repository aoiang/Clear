//
// Created by Yiyang Zhao on 02/12/2017.
//

#ifndef CSCI437_INFINITE_SCREEN_HPP
#define CSCI437_INFINITE_SCREEN_HPP
#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "Screen_Abstract.hpp"

class Infinite_Screen : public Screen_Abstract{
    private:
        sf::Text ro_block_up_button;
        sf::Text dir_block_up_button;
        sf::Text nor_block_up_button;
        sf::Text ro_block_down_button;
        sf::Text dir_block_down_button;
        sf::Text nor_block_down_button;

        sf::FloatRect  item_0_box;
        sf::FloatRect  item_1_box;
        sf::FloatRect  item_2_box;
        sf::FloatRect  item_3_box;
        sf::FloatRect  item_4_box;
        sf::FloatRect  item_5_box;

        sf::Text ro_block_num;
        sf::Text dir_block_num;
        sf::Text nor_block_num;

        sf::Text start;

        int num_of_ro = 0;
        int num_of_dir = 0;
        int num_of_nor = 0;

    public:
        void set(sf::RenderWindow &window);
        int block_size = 50;
        void draw(sf::RenderWindow &window);
        bool check_clicked(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window);
        int *run(sf::RenderWindow &window, int curr_level);






};

#endif //CSCI437_INFINITE_SCREEN_HPP
