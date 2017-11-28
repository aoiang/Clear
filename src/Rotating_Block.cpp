#include "Rotating_Block.hpp"

Rotating_Block::Rotating_Block(int x, int y, int initial_rotation) {
    set_position(x, y);
    set_combine(false);
    reset_rotation();
    while (initial_rotation) {rotate_clockwise(); initial_rotation--;}
    set_id(30 + get_rotation());
    init_tabs();
}

void Rotating_Block::rotate() {
    rotate_clockwise();
    set_id(30 + get_rotation());

}
