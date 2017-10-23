//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMESTATE_H
#define CLEAR_GAMESTATE_H
#include "Block.h"
#include "Normal_Block.h"
#include <SFML/Graphics.hpp>

class GameState {
private:
    Normal_Block normal_block[5];
public:
    void init();
    void block_init();
    Normal_Block * get_Normal_Block();
    bool collision_detector(Normal_Block current_block, std::string direction);
    bool try_move(Normal_Block current_block, std::string direction);
    void try_move(std::string direction);
    void check_mousePosition(sf::RenderWindow App);
    void set_Normal_Block(Normal_Block *normal_block);
};

#endif //CLEAR_GAMESTATE_H
