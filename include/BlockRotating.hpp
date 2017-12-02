#ifndef CLEAR_BLOCKROTATING_HPP
#define CLEAR_BLOCKROTATING_HPP

#include "Block.hpp"
#include <string>

class BlockRotating :public Block {
    public:
        BlockRotating(int, int);
        const static int base_id = ID_ROTATE_0;
};

#endif //CLEAR_BLOCKROTATING_HPP
