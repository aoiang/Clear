#include "BlockGrouped.hpp"

/**BlockGrouped constructor*/
BlockGrouped::BlockGrouped(int x, int y, int group) {
    base_id = ID_GROUPED;
    simple_id = 4;
    rotation_changes_id = false;
    this->group_id = group;
    basic_init(x, y);
}

int BlockGrouped::get_group_id() {return group_id;}
