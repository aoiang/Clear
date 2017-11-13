#include "Block.h"

int x, y, id;
bool can_combine;

/**Sets block id*/
void Block::set_id(int id) {this->id = id;}

void Block::set_combine(bool can_combine) {this->can_combine = can_combine;}

/**Sets block x and y indices on the board*/
void Block::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
  Moves the block
  @param x units to move
  @param y units to move
*/
void Block::move(int x, int y) {
    this->x += x;
    this->y += y;
}


/**@return block id*/
int Block::get_id(){return id;}

/**@return x index of block on board*/
int Block::get_x() {return x;}

/**@return y index of block on board*/
int Block::get_y() {return y;}

/**@return can_combine*/
bool Block::get_combine() {return can_combine;}

//Base block can move in all directions.
bool Block::type_allows_movement(char direction) {return true;}
