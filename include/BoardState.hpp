#ifndef CLEAR_BOARDSTATE_HPP
#define CLEAR_BOARDSTATE_HPP

#include "Block.hpp"
#include <iostream>

class BoardState {
    private:
        int block_ct = 0;
        int block_removed_ct = 0;
        int wrong_moves = 0;
        bool is_clear = false;
        const static int default_width = 9;
        const static int default_height = 9;
        Block * board[default_width][default_height] = {{nullptr}};
        int width;
        int height;
    public:
        BoardState();
        BoardState(int x, int y);
        explicit BoardState(std::string filepath);
        int get_board_width();
        int get_board_height();
        bool is_valid_x(int x);
        bool is_valid_y(int y);
        bool is_valid_location(int x, int y);
        bool remove_block(int x, int y);
        Block * get_block(int x, int y);
        bool block_exists(int x, int y);
        bool add_block(Block * block);
        bool get_is_clear();
        void add_wrong_move();
        int get_blocks_removed_ct();
        void print_board();
        void export_board(std::string filepath);
        std::string export_block(int x, int y);
        Block * import_block(std::string block_identity);
};

#endif //CLEAR_BOARDSTATE_HPP
