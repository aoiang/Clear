#ifndef CLEAR_BLOCKROTATING_HPP
#define CLEAR_BLOCKROTATING_HPP

#include "Block.hpp"
#include <string>

class BlockRotating :public Block {
    public:
        BlockRotating(int, int);
        void init();
        void rotate();
        bool get_combine();
        void set_combine(bool);
};

#endif //CLEAR_BLOCKROTATING_HPP
