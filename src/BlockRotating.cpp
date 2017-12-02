#include "BlockRotating.hpp"

/**BlockRotating constructor*/
BlockRotating::BlockRotating(int x, int y) {
    base_id = ID_ROTATE_0;
    rotation_changes_id = true;
    basic_init(x, y);
}
