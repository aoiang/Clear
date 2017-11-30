#include "Rotating_Block.hpp"

/**Rotating_Block constructor*/
Rotating_Block::Rotating_Block(int x, int y) {
    set_position(x, y);
    reset_rotation();
    set_id(ID_ROTATE_0 + get_rotation());
    init_tabs();
}

/**Rotates the block and updates its ID*/
void Rotating_Block::rotate() {
    rotate_clockwise();
    set_id(ID_ROTATE_0 + get_rotation());
}
