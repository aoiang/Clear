#include "BlockGrouped.hpp"

/**BlockGrouped constructor*/
BlockGrouped::BlockGrouped(int x, int y, int group) {
    base_id = ID_GROUPED;
    simple_id = 4;
    rotation_changes_id = false;
    this->group = group;
    basic_init(x, y);
}

int BlockGrouped::get_group() {return group;}
