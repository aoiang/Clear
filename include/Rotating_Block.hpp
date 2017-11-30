#ifndef CLEAR_ROTATING_BLOCK_HPP
#define CLEAR_ROTATING_BLOCK_HPP

#include "Block.hpp"
#include <string>

class Rotating_Block :public Block {
    public:
        Rotating_Block(int, int);
        void init();
        void rotate();
        bool get_combine();
        void set_combine(bool);
        bool can_rotate(int);
};

#endif //CLEAR_ROTATING_BLOCK_HPP
