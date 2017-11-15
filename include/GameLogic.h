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
        void set_GameBoard(GameBoard &board);
        int get_board_width();
        int get_board_height();
        void set_selected_position(int x, int y);
        int get_selected_x();
        int get_selected_y();
        bool block_exists(int x, int y);
        bool selected_block_exists();
        Block * get_block(int x, int y);
        Block * get_selected_block();
        bool path_blocked(Block * block, char direction);
        bool path_blocked(int x, int y, char direction);
        bool can_be_removed(Block * block);
        bool can_move_block(Block * block, char direction);
        bool tabs_impede(int x, int y, char direction);
        bool can_move(int block_x, int block_y, char direction);
        void try_move(int x, int y, char direction);
        void try_move_selected(char direction);
        bool is_selected_location_valid();
        void remove_block(int x, int y);
};

#endif //GAMELOGIC_H
