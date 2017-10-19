//
// Created by Yiyang Zhao on 18/10/2017.
//

#ifndef CLEAR_NORMAL_BLOCK_H
#define CLEAR_NORMAL_BLOCK_H
#include <string>
#include "Block.h"

class Normal_Block :public Block{
private:
    bool has_direction;
    std::string direction;


public:
    void set_direction(std::string direction);
    std::string get_direction();
    void set_has_direction(bool has_direction);
    bool get_has_direction();
    void init(int id);


};


#endif //CLEAR_NORMAL_BLOCK_H
