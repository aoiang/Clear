#ifndef CLEAR_BOARDSTATE_HPP
#define CLEAR_BOARDSTATE_HPP

#include "Block.hpp"
#include <iostream>
#include <string>

class BoardState {
    private:
        const static int default_width = 9;
        const static int default_height = 9;
        Block * board[default_width][default_height] = {{nullptr}};
        void increase_move_restrictions();
        void decrease_move_restrictions();
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
        bool remove_block(int x, int y, bool modify_restrictions);
        bool add_block(Block * block, bool modify_restrictions);
        bool add_block(Block * block);
        Block * get_block(int x, int y);
        bool block_exists(int x, int y);
        void print_board();
        bool is_clear();
        void export_board(std::string filepath);
        void import_board(std::string filepath);
        std::string export_block(int x, int y);
};

#endif //CLEAR_BOARDSTATE_HPP
