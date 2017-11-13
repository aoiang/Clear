#include "Directional_Block.h"

Directional_Block::Directional_Block(int x, int y, int initial_rotation) {
    set_position(x, y);
    set_combine(false);
    reset_rotation();
    while (initial_rotation) {rotate_clockwise(); initial_rotation--;}
    set_id(20 + get_rotation());
}

void Directional_Block::rotate() {
    rotate_clockwise();
    set_id(20 + get_rotation());
}

bool Directional_Block::type_allows_movement(char direction) {
    return get_direction() == direction;
}
