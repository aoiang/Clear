#ifndef CLEAR_BLOCKDIRECTIONAL_HPP
#define CLEAR_BLOCKDIRECTIONAL_HPP

#include "Block.hpp"

class BlockDirectional :public Block {
    public:
        BlockDirectional(int, int, int);
        const static int base_id = ID_U_DIR;
        bool type_allows_movement(char) override;
};

#endif //CLEAR_BLOCKDIRECTIONAL_HPP
