#include "BlockNormal.hpp"

/**BlockNormal constructor*/
BlockNormal::BlockNormal(int x, int y) {
    set_id(ID_NORMAL);
    set_combine(false);
    set_position(x, y);
    init_tabs();
}

/**@return true because BlockNormal can move in any direction*/
bool BlockNormal::type_allows_movement(char direction) {return true;}
