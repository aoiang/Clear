//
// Created by Yiyang Zhao on 18/10/2017.
//

#include "Rotating_Block.h"


void Rotating_Block::set_combine(bool can_combine)
{
    this->can_combine = can_combine; 
}
void Rotating_Block::init()
{
    this->direction = "clockwise";
    set_combine(true);
}

/*bool Rotating_Block::get_combine()
{
    return this->can_combine;   
}
void Rotating_Block::combine(Block other)
{
    
}
void Rotating_Block::rotate()
{
    
    
}*/
