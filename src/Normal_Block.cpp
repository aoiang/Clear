//
// Created by Yiyang Zhao on 18/10/2017.
//

#include "Normal_Block.h"

/**
  Sets proprties of the Block
  @param x for x position coordinate
  @param y for y position coordinate
  @param speed for block speed when it moves
  @param is_selected for when the block is clicked
  @param id for id
  @param direction is for remove restricted.

*/

void Normal_Block::set_direction(std::string direction){
    this -> direction = direction;
}

std::string Normal_Block::get_direction() {
    return direction;
}

bool Normal_Block::get_has_direction() {
    return has_direction;
}

void Normal_Block::set_has_direction(bool has_direction){
    this ->has_direction = has_direction;
}

void Normal_Block::init(int id) {
    this -> id =id;
    if(id%5 == 0){
        set_has_direction(true);
        this ->direction = "up";
    }
    if(id%5 == 1){
        set_has_direction(true);
        this ->direction = "down";
    }
    if(id%5 == 2){
        set_has_direction(true);
        this ->direction = "left";
    }
    if(id%5 == 3){
        set_has_direction(true);
        this ->direction = "right";
    }
    if(id%5 == 4){
        set_has_direction(false);
    }
}
bool Normal_Block::get_combine()
{
  return this->can_combine;   
}
void Normal_Block::set_combine()
{
  this->can_combine = true;
}
