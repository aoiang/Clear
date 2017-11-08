//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include "Block.h"
#ifndef CLEAR_BOARD_HPP
#define CLEAR_BOARD_HPP

class Clearboard{
    private:
        static int height;
        static int width;
        Block *board [][10];

    public:
        void init();
        void init(int x, int y);
        bool remove(int x, int y);
        Block get_block(int x, int y);
        bool add_block(int x, int y, Block *block);
};

#endif
