#ifndef CLEAR_BLOCKDIRECTIONAL_HPP
#define CLEAR_BLOCKDIRECTIONAL_HPP

#include "Block.hpp"

class BlockDirectional :public Block {
    public:
        BlockDirectional(int, int, int);
        void rotate();
        bool type_allows_movement(char);
        char get_direction();
};

#endif //CLEAR_BLOCKDIRECTIONAL_HPP
