#ifndef CLEAR_GAMELOGIC_HPP
#define CLEAR_GAMELOGIC_HPP

#include "Block.hpp"
#include "BlockNormal.hpp"
#include "BlockDirectional.hpp"
#include "BlockRotating.hpp"
#include "BoardState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameLogic {
    private:
        BoardState * board;
        int selected_x = -1;
        int selected_y = -1;
    public:
        void set_BoardState(BoardState &board);
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
        bool tabs_impede(Block * block, char direction);
        bool can_move(int block_x, int block_y, char direction);
        bool try_move(int x, int y, char direction);
        bool try_move_selected(char direction);
        bool is_selected_location_valid();
        void remove_block(int x, int y);
        bool tap_selected();
        bool get_is_clear();
        void add_wrong_move();
        int get_blocks_removed_ct();
        bool block_is_move_restricted(int, int);
        bool selected_block_is_move_restricted();
};

#endif //CLEAR_GAMELOGIC_HPP
