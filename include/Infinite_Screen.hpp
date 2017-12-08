#ifndef CSCI437_INFINITE_SCREEN_HPP
#define CSCI437_INFINITE_SCREEN_HPP

#include "Screen_Abstract.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Infinite_Screen : public Screen_Abstract {
    private:
        sf::Text button[10];
        sf::Text block_num[5];
        sf::Text title;
        sf::Text board_size;
        sf::Text start;
        int num_of_blocks[5];
        std::string block_counts[3];
        bool clicked = false;
        sf::RectangleShape normal_block;
        sf::RectangleShape rotating_block;
        sf::RectangleShape directional_block;
        int normal_frequency;
        int rotating_frequency;
        int directional_frequency;
        int width;
        int height;
        

    public:
        Infinite_Screen();
        void draw();
        int run();
};

#endif //CSCI437_INFINITE_SCREEN_HPP
