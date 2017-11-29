#ifndef CLEAR_ROTATION_AWARE_BLOCK_HPP
#define CLEAR_ROTATION_AWARE_BLOCK_HPP

#include "Block.hpp"

static char directions[5] = "urdl";

class Rotation_Aware_Block :public Block {
    private:
        int rotation;
    protected:
        void rotate_clockwise();
        void reset_rotation();
    public:
        int get_rotation();
        char get_direction();
};

#endif //CLEAR_ROTATION_AWARE_BLOCK_HPP
