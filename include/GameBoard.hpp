#ifndef CLEAR_BOARD_HPP
#define CLEAR_BOARD_HPP

#include "Block.hpp"
#include <iostream>

class GameBoard {
    private:
        int block_ct = 0;
        int block_removed_ct = 0;
        int wrong_moves = 0;
        bool is_clear = false;
        const static int default_width = 9;
        const static int default_height = 9;
        Block * board[default_width][default_height] = {{0}};
        int width;
        int height;
        void init(int x, int y);

    public:
        void init();
        int get_board_width();
        int get_board_height();
        int is_valid_x(int x);
        int is_valid_y(int y);
        int is_valid_location(int x, int y);
        bool remove_block(int x, int y);
        Block * get_block(int x, int y);
        bool block_exists(int x, int y);
        bool add_block(Block * block);
        bool get_is_clear();
        void add_wrong_move();
};

#endif //GAMEBOARD_HPP
