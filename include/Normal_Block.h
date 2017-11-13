#ifndef CLEAR_NORMAL_BLOCK_H
#define CLEAR_NORMAL_BLOCK_H
#include "Block.h"

class Normal_Block :public Block {
    public:
        Normal_Block(int x, int y);
        bool type_allows_movement(char direction);
};


#endif //CLEAR_NORMAL_BLOCK_H