#ifndef CLEAR_ROTATING_BLOCK_HPP
#define CLEAR_ROTATING_BLOCK_HPP

#include "Block.hpp"
#include <string>

class Rotating_Block :public Block {
    private:
        std::string direction;
    public:
        void init();
        //void rotate();
        //void combine(Block other);
        bool get_combine();
        void set_combine(bool can_combine);

};

#endif //CLEAR_ROTATING_BLOCK_HPP
