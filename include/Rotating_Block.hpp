#ifndef CLEAR_ROTATING_BLOCK_HPP
#define CLEAR_ROTATING_BLOCK_HPP

#include "Rotation_Aware_Block.hpp"
#include <string>

class Rotating_Block :public Rotation_Aware_Block {
    public:
        Rotating_Block(int, int, int);
        void init();
        void rotate();
        //void combine(Block other);
        bool get_combine();
        void set_combine(bool can_combine);
};

#endif //CLEAR_ROTATING_BLOCK_HPP
