#include "Block.hpp"

int x, y, id;
bool can_combine;

/**Sets block id*/
void Block::set_id(int id) {this->id = id;}

/**Sets whether or not a block can combine*/
void Block::set_combine(bool can_combine) {this->can_combine = can_combine;}

/**Sets block x and y indices on the board*/
void Block::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

/**@return block id*/
int Block::get_id(){return id;}

/**@return x index of block on board*/
int Block::get_x() {return x;}

/**@return y index of block on board*/
int Block::get_y() {return y;}

/**@return index based on direction*/
int Block::dir_to_index(char dir) {
    if (dir == 'u') {return 0;}
    else if (dir == 'r') {return 1;}
    else if (dir == 'd') {return 2;}
    else if (dir == 'l') {return 3;}
    else {return -1;}
}

/**Sets whether a tab exists or not*/
void Block::set_tab(char dir, bool tab) {
    tabs[dir_to_index(dir)] = tab;
}

/**Gets whether or not a tab exists*/
bool Block::get_tab(char dir) {
    return tabs[dir_to_index(dir)];
}

/**Sets tabs to 0*/
void Block::init_tabs() {
    set_tab('l', 0);
    set_tab('r', 0);
    set_tab('u', 0);
    set_tab('d', 0);
}

/**@return can_combine*/
bool Block::get_combine() {return can_combine;}

/**Gets whether or not a block can move in a given direction*/
//Base block can move in all directions.
bool Block::type_allows_movement(char direction) {return true;}

/**Sets how many block clears are required before removal*/
void Block::set_move_restriction(int steps) {move_restriction = steps;}

int Block::get_rotation() {return rotation;}

char Block::get_direction() {return directions[get_rotation()];}

void Block::rotate_clockwise() {
    rotation = (rotation + 1) % 4;
    int tmp = tabs[3];
    for (int i = 3; i > 0; i--) {
        tabs[i] = tabs[i-1];
    }
    tabs[0] = tmp;
}

void Block::reset_rotation() {rotation = 0;}
