//
// Created by Yiyang Zhao on 18/10/2017.
//

#ifndef CLEAR_NORMAL_BLOCK_H
#define CLEAR_NORMAL_BLOCK_H
#include <string>
#include "Block.h"


static char directions[4][10] = {"up","down","left","right"};//TODO need to be null terminated?

/**
 * This class is for normal block which has directions.
 */
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
    bool get_combine();
    void set_combine();
};


#endif //CLEAR_NORMAL_BLOCK_H