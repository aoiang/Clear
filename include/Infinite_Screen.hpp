#ifndef CSCI437_INFINITE_SCREEN_HPP
#define CSCI437_INFINITE_SCREEN_HPP
#include "Screen_Abstract.hpp"
#include "GameLogic.hpp"
#include "GameView_Screen.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Infinite_Screen : public Screen_Abstract {
    private:
        sf::Text button[10];
        sf::FloatRect item_box[10];
        sf::Text block_num[5];
        sf::Text start;
        int num_of_blocks[5];
        std::string block_counts[3];
        bool clicked = false;

    public:
        void counts_of_block();
        void init();
        int block_size = 50;
        void draw();
        int run();
};

#endif //CSCI437_INFINITE_SCREEN_HPP
