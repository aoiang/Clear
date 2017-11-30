#ifndef CLEAR_DIRECTIONAL_BLOCK_HPP
#define CLEAR_DIRECTIONAL_BLOCK_HPP

#include "Block.hpp"

class Directional_Block :public Block {
    public:
        Directional_Block(int, int, int);
        void rotate();
        bool type_allows_movement(char);
        char get_direction();
};

#endif //CLEAR_DIRECTIONAL_BLOCK_HPP
