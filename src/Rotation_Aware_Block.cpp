#include "Rotation_Aware_Block.h"


int rotation = 0;

int Rotation_Aware_Block::get_rotation() {return rotation%4;}
char Rotation_Aware_Block::get_direction() {return directions[get_rotation()];}
void Rotation_Aware_Block::rotate_clockwise() {rotation += 1;}
void Rotation_Aware_Block::reset_rotation() {rotation = 0;}
//eventually have overflow issue etc.
