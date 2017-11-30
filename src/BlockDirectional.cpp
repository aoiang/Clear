#include "BlockDirectional.hpp"

/**Constructor for BlockDirectional*/
BlockDirectional::BlockDirectional(int x, int y, int initial_rotation) {
    set_position(x, y);
    set_combine(false);
    reset_rotation();
    while (initial_rotation) {rotate_clockwise(); initial_rotation--;}
    set_id(ID_U_DIR + get_rotation());
    init_tabs();
}

/**Rotates the block, updates the block's ID*/
void BlockDirectional::rotate() {
    rotate_clockwise();
    set_id(ID_U_DIR + get_rotation());
}

/**@return the direction of the block*/
char BlockDirectional::get_direction() {return directions[get_rotation()];}

/**@return if the block can move in a given direction*/
bool BlockDirectional::type_allows_movement(char direction) {return (get_direction() == direction);}
