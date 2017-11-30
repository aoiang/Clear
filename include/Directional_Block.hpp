#ifndef CLEAR_DIRECTIONAL_BLOCK_HPP
#define CLEAR_DIRECTIONAL_BLOCK_HPP

#include "Block.hpp"

class Directional_Block :public Block {
    public:
        Directional_Block(int x, int y, int initial_rotation);
        void rotate();
        bool type_allows_movement(char direction);
};

#endif //CLEAR_DIRECTIONAL_BLOCK_HPP
