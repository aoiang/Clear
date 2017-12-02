#ifndef CLEAR_BLOCKNORMAL_HPP
#define CLEAR_BLOCKNORMAL_HPP

#include "Block.hpp"

class BlockNormal :public Block {
    public:
        BlockNormal(int, int);
        const static int base_id = ID_NORMAL;
};

#endif //CLEAR_BLOCKNORMAL_HPP
