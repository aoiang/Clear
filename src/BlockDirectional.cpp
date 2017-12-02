#include "BlockDirectional.hpp"

/**Constructor for BlockDirectional*/
BlockDirectional::BlockDirectional(int x, int y, int initial_rotation) {
    rotation_changes_id = true;
    basic_init(x, y);
    while (initial_rotation) {rotate(); initial_rotation--;}
    set_id();
}

/**@return if the block can move in a given direction*/
bool BlockDirectional::type_allows_movement(char direction) {return (get_direction() == direction);}
