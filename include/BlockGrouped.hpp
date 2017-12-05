#ifndef CLEAR_BLOCKGROUPED_HPP
#define CLEAR_BLOCKGROUPED_HPP

#include "Block.hpp"

class BlockGrouped :public Block {
    private:
        int group_id;
    public:
        BlockGrouped(int, int, int);
        int get_group_id();
};

#endif //CLEAR_BLOCKGROUPED_HPP
