//
// Created by Yiyang Zhao on 16/10/2017
// Additional work by Ivan Echevarria
//


#include "Block.h"


float Block::get_length() {
    return length;
}

float Block::get_width() {
    return width;
}

void Block::set_length(float length) {
    this -> length = length;
}

void Block::set_width(float width) {
    this -> width = width;
}

int Block::get_id(){
    return id;
}

void Block::set_id(int id) {
    this ->id = id;
}

void Block::init(int id) {
    this->length = 50;
    this->width = 50;
    this ->id = id;
}

void Block::setX(float x) {
    this -> x = x;
}

void Block::setY(float y) {
    this -> y = y;
}

void Block::setPosition(float x, float y) {
    this -> x = x;
    this -> y = y;
}

float Block::getX() {
    return x;
}

float Block::getY() {
    return y;
}

void Block::move(float x, float y) {
    this -> x += x;
    this -> y += y;
}

bool Block::get_combine() {
    return can_combine;
}

void Block::set_combine(bool can_combine) {
    this -> can_combine = can_combine;
}
