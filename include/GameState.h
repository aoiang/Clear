//
// Created by Yiyang Zhao on 22/10/2017.
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
    Normal_Block* get_Normal_Block();
    void check_keyboard_in();
    bool collision_detector(Normal_Block current_block, std::string direction);
    void check_mousePosition(sf::RenderWindow App);
    void set_Normal_Block(Normal_Block *normal_block);



};


#endif //CLEAR_GAMESTATE_H
