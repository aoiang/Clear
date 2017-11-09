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
void Block::setX(float x) {
    this -> x = x;
}


/**
  Sets block y index on the board
  @param y
*/
void Block::setY(float y) {
    this -> y = y;
}


/**
  Sets block x and y indices on the board
  @param x
  @param y
*/
void Block::setPosition(float x, float y) {
    this -> x = x;
    this -> y = y;
}


/**
  @return x index of block on board
*/
float Block::getX() {
    return x;
}


/**
  @return y index of block on board
*/
float Block::getY() {
    return y;
}


/**
  Moves the block
  @param x units to move
  @param y units to move
*/
void Block::move(float x, float y) {
    this -> x += x;
    this -> y += y;
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
