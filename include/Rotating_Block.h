//
// Created by Yiyang Zhao on 18/10/2017.
//

#ifndef CLEAR_ROTATING_BLOCK_H
#define CLEAR_ROTATING_BLOCK_H

#include <Block.h>
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

#endif //CLEAR_ROTATING_BLOCK_H
