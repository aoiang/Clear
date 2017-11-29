#include "Normal_Block.hpp"

Normal_Block::Normal_Block(int x, int y) {
    set_id(ID_NORMAL);
    set_combine(false);
    set_position(x, y);
    init_tabs();
}

bool Normal_Block::type_allows_movement(char direction) {return true;}
