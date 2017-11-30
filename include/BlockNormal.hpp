#ifndef CLEAR_BLOCKNORMAL_HPP
#define CLEAR_BLOCKNORMAL_HPP

#include "Block.hpp"

class BlockNormal :public Block {
    public:
        BlockNormal(int, int);
        bool type_allows_movement(char);
};

#endif //CLEAR_BLOCKNORMAL_HPP
