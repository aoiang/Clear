//
//created by Yosef Ejigu 10/21/17
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
        
};

#endif
