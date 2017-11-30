#ifndef CLEAR_NORMAL_BLOCK_HPP
#define CLEAR_NORMAL_BLOCK_HPP

#include "Block.hpp"

class Normal_Block :public Block {
    public:
        Normal_Block(int, int);
        bool type_allows_movement(char);
};

#endif //CLEAR_NORMAL_BLOCK_HPP
