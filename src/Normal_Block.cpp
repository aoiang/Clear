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

void Normal_Block::set_direction(std::string direction) {this->direction = direction;}

std::string Normal_Block::get_direction() {return direction;}

bool Normal_Block::get_has_direction() {return has_direction;}

void Normal_Block::set_has_direction(bool has_direction) {this->has_direction = has_direction;}

void Normal_Block::init(int id) {
    this->id = id;
    //TODO really should just set it with set_has_direction(id%5==4); and add an entry in directions for having none.
    if (id%5==4) {set_has_direction(false);}
    else {
        set_has_direction(true);
        this->direction = directions[id%5];
    }
}

bool Normal_Block::get_combine() {return this->can_combine;}

void Normal_Block::set_combine() {this->can_combine = true;}

bool Block::type_allows_movement(std::string direction) {
    if (dir == "up") {
        return this->direction == directions[0];
    } else if (dir == "right") {
        return this->direction == directions[3];
    } else if (dir == "down") {
        return this->direction == directions[1];
    } else if (dir == "left") {
        return this->direction == directions[2];
    }
}
