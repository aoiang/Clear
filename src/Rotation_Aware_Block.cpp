#include "Rotation_Aware_Block.hpp"

int rotation = 0;

int Rotation_Aware_Block::get_rotation() {
    return rotation;
}

char Rotation_Aware_Block::get_direction() {
    return directions[get_rotation()];
}

void Rotation_Aware_Block::rotate_clockwise() {
    rotation = (rotation + 1) % 4;
    int tmp = tabs[3];
    for (int i = 3; i > 0; i--) {
        tabs[i] = tabs[i-1];
    }
    tabs[0] = tmp;
}

void Rotation_Aware_Block::reset_rotation() {
    rotation = 0;
}
