//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMELOGIC_H
#define CLEAR_GAMELOGIC_H

#include "Block.h"
#include "Normal_Block.h"
#include <SFML/Graphics.hpp>

class GameLogic {
private:
    Normal_Block board_array[5];
public:
    void init();
    void block_init();
    Normal_Block * get_board_array();
    bool collision_detector(Normal_Block current_block, std::string direction);
    void try_move(std::string direction);
    void check_mousePosition(sf::RenderWindow App);
    void set_board_array(Normal_Block *board_array);
};

#endif
