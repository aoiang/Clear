#include "Normal_Block.h"

Normal_Block::Normal_Block(int x, int y) {
    set_id(10);
    set_combine(false);
    set_position(x, y);
}

bool Normal_Block::type_allows_movement(char direction) {return true;}
