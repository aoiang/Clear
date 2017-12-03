#include <vector>
#include <BlockRotating.hpp>
#include <BlockDirectional.hpp>
#include <BlockNormal.hpp>
#include "Block.hpp"
#include "Definitions.hpp"

/**Sets block id*/
void Block::set_id() {
    id = base_id;
    if (rotation_changes_id) {id += get_rotation();}
}

/**Sets whether or not a block can combine*/
void Block::set_combine(bool can_combine) {this->can_combine = can_combine;}

/**Sets block x and y indices on the board*/
void Block::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

/**@return block id*/
int Block::get_id() {return id;}

/**@return x index of block on board*/
int Block::get_x() {return x;}

/**@return y index of block on board*/
int Block::get_y() {return y;}

/**@return index based on direction*/
int Block::dir_to_index(char dir) {
    switch (dir) {
        case U_DIR: return 0;
        case R_DIR: return 1;
        case D_DIR: return 2;
        case L_DIR: return 3;
        default: return -1;
    }
}

/**Sets whether a tab exists or not*/
void Block::set_tab(char dir, bool tab_exists) {
    tabs[dir_to_index(dir)] = tab_exists;
}

/**@return whether or not a block exists on a side of the block*/
bool Block::get_tab(char dir) {
    return tabs[dir_to_index(dir)];
}

/**Sets all tabs to 0*/
void Block::init_tabs() {
    set_tab(U_DIR, false);
    set_tab(R_DIR, false);
    set_tab(D_DIR, false);
    set_tab(L_DIR, false);
}

/**@return can_combine*/
bool Block::get_combine() {return can_combine;}

/**Gets whether or not a block can move in a given direction*/
//Base block can move in all directions.
bool Block::type_allows_movement(char direction) {return true;}

/**@return if fewer blocks have been removed from board than are needed*/
bool Block::is_move_restricted(int steps) {return steps<move_restriction;}

/**Sets how many block clears are required before removal*/
void Block::set_move_restriction(int steps) {move_restriction = steps;}

/**Gets the integer representing block rotation*/
int Block::get_rotation() {return rotation;}

/**Rotates the block and its tabs clockwise*/
void Block::rotate() {
    rotation = (rotation+1)%4;
    bool tmp = tabs[3];
    for (int i=3; i>0; i--) {tabs[i] = tabs[i-1];}
    tabs[0] = tmp;
    set_id();
}

/**Resets rotation to 0*/
void Block::reset_rotation() {rotation = 0;}

/**@return number of moves before this can be removed*/
int Block::get_move_restriction() {return move_restriction;}


/**@return the direction of the block*/
char Block::get_direction() {return directions[get_rotation()];}


void Block::basic_init(int x, int y) {
    set_position(x, y);
    set_combine(false);
    reset_rotation();
    set_id();
    init_tabs();
    set_move_restriction(0);
}

void Block::import_init(std::string identity) {
    std::vector<std::string> characteristics = split_string(identity, ',');
    int imported_simple_id, imported_rotation, imported_move_restriction;
    bool imported_tab_up, imported_tab_right, imported_tab_down, imported_tab_left, imported_combine;

    imported_simple_id = stoi(characteristics[0]);
    imported_rotation = stoi(characteristics[1]);
    imported_tab_up = string_to_bool(characteristics[3].substr(0, 1));
    imported_tab_right = string_to_bool(characteristics[3].substr(1, 1));
    imported_tab_down = string_to_bool(characteristics[3].substr(2, 1));
    imported_tab_left = string_to_bool(characteristics[3].substr(3, 1));
    imported_combine = string_to_bool(characteristics[2]);
    imported_move_restriction = stoi(characteristics[4]);


    //get_rotation(), get_combine(), get_tab('u')(x4), get_move_restriction()(potentially high)

    if (imported_simple_id != simple_id) {std::cout << "Badly Initialized Block" << std::endl;}
    set_combine(imported_combine);
    while (imported_rotation) {rotate(); imported_rotation--;}
    set_move_restriction(imported_move_restriction);
    set_tab(U_DIR, imported_tab_up);
    set_tab(R_DIR, imported_tab_right);
    set_tab(D_DIR, imported_tab_down);
    set_tab(L_DIR, imported_tab_left);
}

char Block::bool_to_char(bool boolean) {
    if (boolean) {return 't';}
    else {return 'f';}
}

bool Block::string_to_bool(std::string text) {
    return text == "t";
}



std::vector<std::string> Block::split_string(const std::string &text, char delimiter) {
    // Adapted from https://stackoverflow.com/a/7408245
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end-start));
        start = end+1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

Block * Block::import_block(std::string identity, int x, int y) {
    Block * block;
    int imported_simple_id = stoi(split_string(identity, ',')[0]);
    switch (imported_simple_id) {
        case 1:
            block = new BlockNormal(x, y);
            break;
        case 2:
            block = new BlockDirectional(x, y, 0);
            break;
        case 3:
            block = new BlockRotating(x, y);
            break;
        default:
            block = nullptr;
            std::cout << "Bad ID in import_block: " << imported_simple_id << " from identity: " << identity << std::endl;
            break;
    }
    block->import_init(identity);
    return block;
}

std::string Block::get_identity() {
    //simple_id, get_rotation(), get_combine(), get_tab('u')(x4), get_move_restriction()(potentially high)
    std::string tabs;
    tabs += bool_to_char(get_tab(U_DIR));
    tabs += bool_to_char(get_tab(R_DIR));
    tabs += bool_to_char(get_tab(D_DIR));
    tabs += bool_to_char(get_tab(L_DIR));
    std::string identity = std::to_string(simple_id) + ","
                         + std::to_string(get_rotation()) + ","
                         + bool_to_char(get_combine()) + ","
                         + tabs + ","
                         + std::to_string(get_move_restriction());
    return identity;
}


