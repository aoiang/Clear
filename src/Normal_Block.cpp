#include "Normal_Block.hpp"

/**Normal_Block constructor*/
Normal_Block::Normal_Block(int x, int y) {
    set_id(ID_NORMAL);
    set_combine(false);
    set_position(x, y);
    init_tabs();
}

/**@return true because Normal_Block can move in any direction*/
bool Normal_Block::type_allows_movement(char direction) {return true;}
