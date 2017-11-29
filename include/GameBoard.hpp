#ifndef CLEAR_BOARD_HPP
#define CLEAR_BOARD_HPP

#include "Block.hpp"
#include <iostream>

class GameBoard {
    private:
        const static int default_width = 10;
        const static int default_height = 10;
        Block * board[default_width][default_height] = {{0}};
        int width;
        int height;

    public:
        void init();
        void init(int x, int y);
        int get_board_width();
        int get_board_height();
        int is_valid_x(int x);
        int is_valid_y(int y);
        int is_valid_location(int x, int y);
        bool remove_block(int x, int y);
        Block * get_block(int x, int y);
        bool block_exists(int x, int y);
        bool add_block(Block * block);
};

#endif //GAMEBOARD_HPP
