//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include "Block.h"
#ifndef CLEAR_BOARD_HPP
#define CLEAR_BOARD_HPP

class GameBoard {
    private:
        int board[10][10] = {{0}};
        int width = 10;
        int height = 10;

    public:
        void init();
        void init(int x, int y);
        void remove_block(int x, int y);
        int get_block(int x, int y);
        int get_width();
        int get_height();
        int get_block();
};

#endif
