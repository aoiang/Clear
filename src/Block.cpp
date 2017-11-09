//
// Created by Yiyang Zhao on 16/10/2017
// Additional work by Ivan Echevarria
//


#include "Block.h"


/**
  @return block id
*/
int Block::get_id(){
    return id;
}


/**
  Sets block id
  @param id
*/
void Block::set_id(int id) {
    this ->id = id;
}


/**
  Initializes block, sets id
  @param id
*/
void Block::init(int id) {
    this ->id = id;
}


/**
  Sets block x index on the board
  @param x
*/
void Block::set_row(float row) {
    this -> row = row;
}


/**
  Sets block y index on the board
  @param y
*/
void Block::set_col(float col) {
    this -> col = col;
}


/**
  Sets block x and y indices on the board
  @param x
  @param y
*/
void Block::setPosition(float row, float col) {
    this -> row = row;
    this -> col = col;
}


/**
  @return x index of block on board
*/
float Block::get_row() {
    return row;
}


/**
  @return y index of block on board
*/
float Block::get_col() {
    return col;
}


/**
  Moves the block
  @param x units to move
  @param y units to move
*/
void Block::move(float row, float y) {
    this -> row += row;
    this -> col += col;
}


/**
  @return can_combine
*/
bool Block::get_combine() {
    return can_combine;
}


/**
  Sets if Block can combine
  @param can_combine
*/
void Block::set_combine(bool can_combine) {
    this -> can_combine = can_combine;
}
