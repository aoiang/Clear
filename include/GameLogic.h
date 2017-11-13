//
// Created by Yiyang Zhao on 22/10/2017
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMELOGIC_H
#define CLEAR_GAMELOGIC_H

#include "Block.h"
#include "Normal_Block.h"
#include "Directional_Block.h"
#include "GameBoard.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameLogic {
    private:
        GameBoard * board;
        int selected_x = -1;
        int selected_y = -1;
    public:
        bool path_blocked(int x, int y, char direction);
        bool can_move(int block_x, int block_y, char direction);
        void try_move(int x, int y, char direction);
        void try_move_selected(char direction);
        void check_mousePosition(sf::RenderWindow App);
        void set_GameBoard(GameBoard &board);
    
        int get_selected_x();
        int get_selected_y();
        Block * get_selected_block();
        void set_selected_position(int x, int y);
        bool is_selected_location_valid();
        bool block_exists(int x, int y);
        bool selected_block_exists();
        int get_board_width();
        int get_board_height();
        
        Block * get_block(int x, int y);
        void remove_block(int x, int y);
};

#endif
