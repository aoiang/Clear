#include "GameLogic.hpp"

/**Sets BoardState*/
void GameLogic::set_BoardState(BoardState &board) {
    this->board = &board;
    state->init_current_board();
}

/**Sets GameState*/
void GameLogic::set_GameState(GameState &state) {this->state = &state;};

/**@return x index of selected block*/
int GameLogic::get_selected_x() {return selected_x;}

/**@return y index of selected block*/
int GameLogic::get_selected_y() {return selected_y;}

/**Sets postion of selected block_shape*/
void GameLogic::set_selected_position(int x, int y) {
    selected_x = x;
    selected_y = y;
}

//TODO why should the selected block ever be invalid? should just check validity when setting.
/**Checks if selected location is valid*/
bool GameLogic::is_selected_location_valid() {return board->is_valid_location(selected_x, selected_y);}

/**Checks if block exists at index*/
bool GameLogic::block_exists(int x, int y) {return board->block_exists(x,y);}

/**Checks if the selected block exists*/
bool GameLogic::selected_block_exists() {return block_exists(selected_x, selected_y);}

/**@return block type integer*/
Block * GameLogic::get_block(int x, int y) {return board->get_block(x, y);}

/**@return selected block*/
Block * GameLogic::get_selected_block() {return get_block(selected_x, selected_y);}

/**@return board width*/
int GameLogic::get_board_width() {return board->get_board_width();}

/**@return board height*/
int GameLogic::get_board_height() {return board->get_board_height();}

/**Checks if tabs restrict a block's movement*/
bool GameLogic::tabs_impede(Block * block, char direction) {
    switch (direction) {
        case U_DIR: case D_DIR:
            return side_is_tablocked(block, L_DIR) || side_is_tablocked(block, R_DIR);
        case L_DIR: case R_DIR:
            return side_is_tablocked(block, U_DIR) || side_is_tablocked(block, D_DIR);
        default:break;
    }
}

/**Checks if tabs always restrict a block's movement*/
bool GameLogic::tabs_always_impede(Block * block, char direction) {
    return tabs_impede(block, direction) && !tabs_temporarily_impede(block, direction);
}

/**Checks if tabs restrict a block's movement even if it and adjacent blocks are rotated.*/
bool GameLogic::tabs_temporarily_impede(Block * block, char direction) {
    if (!tabs_impede(block, direction)) {return false;}
    bool self_tabs_fine = !movement_is_tablocked_by_self(block, direction) || movement_is_temporarily_tablocked_by_self(block, direction);
    bool adjacent_tabs_fine = !movement_is_tablocked_by_adjacent(block, direction) || movement_is_temporarily_tablocked_by_adjacent(block, direction);
    return self_tabs_fine && adjacent_tabs_fine;
}

/**Checks if the axis's tablocked status can be removed by rotating the block.*/
bool GameLogic::movement_is_tablocked_by_adjacent(Block * block, char direction) {
    switch (direction) {
        case U_DIR: case D_DIR: return side_is_tablocked_by_adjacent(block, L_DIR) || side_is_tablocked_by_adjacent(block, R_DIR);
        case L_DIR: case R_DIR: return side_is_tablocked_by_adjacent(block, U_DIR) || side_is_tablocked_by_adjacent(block, D_DIR);
        default:break;
    }
}

/**Checks if the axis's tablocked status can be removed by rotating the block.*/
bool GameLogic::movement_is_temporarily_tablocked_by_adjacent(Block * block, char direction) {
    bool movement_tablocked_by_adjacent = movement_is_tablocked_by_adjacent(block, direction);
    if (!movement_tablocked_by_adjacent) {return false;}
    switch (direction) {
        case U_DIR: case D_DIR: return !side_is_always_tablocked_by_adjacent(block, L_DIR) && !side_is_always_tablocked_by_adjacent(block, R_DIR);
        case L_DIR: case R_DIR: return !side_is_always_tablocked_by_adjacent(block, U_DIR) && !side_is_always_tablocked_by_adjacent(block, D_DIR);
        default:break;
    }
}


/**Checks if the axis's tablocked status can be removed by rotating the block.*/
bool GameLogic::movement_is_tablocked_by_self(Block * block, char direction) {
    switch (direction) {
        case U_DIR: case D_DIR: return side_is_tablocked_by_self(block, L_DIR) || side_is_tablocked_by_self(block, R_DIR);
        case L_DIR: case R_DIR: return side_is_tablocked_by_self(block, U_DIR) || side_is_tablocked_by_self(block, D_DIR);
        default:break;
    }
}

/**Checks if the axis's tablocked status can be removed by rotating the block.*/
bool GameLogic::movement_is_temporarily_tablocked_by_self(Block * block, char direction) {
    bool movement_tablocked_by_self = movement_is_tablocked_by_self(block, direction);
    if (!movement_tablocked_by_self) {return false;}
    bool block_is_rotateable = block->get_simple_id()==3;
    bool tab_configuration_is_ok = (!block->get_tab(U_DIR) && !block->get_tab(D_DIR))
                                || (!block->get_tab(R_DIR) && !block->get_tab(L_DIR));
    return block_is_rotateable
        && movement_tablocked_by_self//for clarity
        && tab_configuration_is_ok;
}

/**Checks if one of the block's sides has an adjacent block; and either of the two blocks have a tab on that shared side.*/
bool GameLogic::side_is_tablocked(Block * block, char direction) {
    return side_is_tablocked_by_adjacent(block, direction)
        || side_is_tablocked_by_self(block, direction);
}


bool GameLogic::side_is_temporarily_tablocked(Block * block, char direction) {
    return side_is_temporarily_tablocked_by_adjacent(block, direction)
        || side_is_temporarily_tablocked_by_self(block, direction);
}


bool GameLogic::side_is_always_tablocked_by_adjacent(Block * block, char direction) {
    return side_is_tablocked_by_adjacent(block, direction)
       && !side_is_temporarily_tablocked_by_adjacent(block, direction);
}

/**Checks if one of the block's sides has an adjacent block with a tab on the shared side.*/
bool GameLogic::side_is_tablocked_by_adjacent(Block * block, char direction) {
    int x = block->get_x();
    int y = block->get_y();
    switch (direction) {
        case U_DIR: return block_exists(x, y+1) && get_block(x, y+1)->get_tab(D_DIR);
        case D_DIR: return block_exists(x, y-1) && get_block(x, y-1)->get_tab(U_DIR);
        case L_DIR: return block_exists(x-1, y) && get_block(x-1, y)->get_tab(R_DIR);
        case R_DIR: return block_exists(x+1, y) && get_block(x+1, y)->get_tab(L_DIR);
        default:break;
    }
}

/**Checks if the side's tablocked status can be removed by rotating the adjacent block.*/
bool GameLogic::side_is_temporarily_tablocked_by_adjacent(Block * block, char direction) {
    bool adjacent_block_is_tablocking = side_is_tablocked_by_adjacent(block, direction);
    if (!adjacent_block_is_tablocking) {return false;}//can now assume (below) that the adjacent block exists
    int x = block->get_x();
    int y = block->get_y();
    Block * adjacent_block;
    switch (direction) {
        case U_DIR: adjacent_block = get_block(x, y+1); break;
        case D_DIR: adjacent_block = get_block(x, y-1); break;
        case L_DIR: adjacent_block = get_block(x-1, y); break;
        case R_DIR: adjacent_block = get_block(x+1, y); break;
        default:break;
    }
    bool adjacent_block_is_rotateable = adjacent_block->get_simple_id()==3;
    bool adjacent_block_is_not_fully_tabbed = adjacent_block->get_tab_count()!=4;
    return adjacent_block_is_rotateable
        && adjacent_block_is_tablocking//for clarity
        && adjacent_block_is_not_fully_tabbed;
}

/**Checks if one of the block's sides has an adjacent block and a tab on the shared side.*/
bool GameLogic::side_is_tablocked_by_self(Block * block, char direction) {
    int x = block->get_x();
    int y = block->get_y();
    switch (direction) {
        case U_DIR: return block_exists(x, y+1) && block->get_tab(U_DIR);
        case D_DIR: return block_exists(x, y-1) && block->get_tab(D_DIR);
        case L_DIR: return block_exists(x-1, y) && block->get_tab(L_DIR);
        case R_DIR: return block_exists(x+1, y) && block->get_tab(R_DIR);
        default:break;
    }
}

/**Checks if the side's tablocked status can be removed by rotating the adjacent block.*/
bool GameLogic::side_is_temporarily_tablocked_by_self(Block * block, char direction) {
    bool block_is_tablocking = side_is_tablocked_by_self(block, direction);
    if (!block_is_tablocking) {return false;}//can now assume (below) that the adjacent block exists
    bool block_is_rotateable = block->get_simple_id()==3;
    bool block_is_not_fully_tabbed = block->get_tab_count()!=4;
    return block_is_rotateable
        && block_is_tablocking//for clarity
        && block_is_not_fully_tabbed;
}

/**Checks if a direction relative to a block is clear or blocked.*/
bool GameLogic::path_blocked(Block * block, char direction) {
    int x = block->get_x();
    int y = block->get_y();
    return path_blocked(x, y, direction);
}

/**@return if a block's path is blocked*/
bool GameLogic::path_blocked(int x, int y, char direction) {
    switch (direction) {
        case U_DIR:
            for (int y2 = y+1; y2<get_board_height(); y2++) {
                if (block_exists(x, y2)) {return true;}
            } break;
        case R_DIR:
            for (int x2 = x+1; x2<get_board_width(); x2++) {
                if (block_exists(x2, y)) {return true;}
            } break;
        case D_DIR:
            for (int y2 = y-1; y2>=0; y2--) {
                if (block_exists(x, y2)) {return true;}
            } break;
        case L_DIR:
            for (int x2 = x-1; x2>=0; x2--) {
                if (block_exists(x2, y)) {return true;}
            } break;
        default:break;
    }
    return false;
}

/**@return if location is fully blocked*/
bool GameLogic::path_fully_blocked(int x, int y) {
    return path_blocked(x, y, U_DIR)
        && path_blocked(x, y, R_DIR)
        && path_blocked(x, y, D_DIR)
        && path_blocked(x, y, L_DIR);
}

/**Removes block at index x,y*/
//TODO remove hard coded string
void GameLogic::remove_block(int x, int y) {
    std::cout << "Removed block at " << x << ", " << y << "\n";
    board->remove_block(x, y);
    state->increment_blocks_removed();
    set_selected_position(-1, -1);
    if (board->is_clear()) {
        std::cout << std::endl << "Board is clear" << std::endl << std::endl;
    }
}

bool GameLogic::block_allows_movement(Block * block, char direction) {
    bool type_allows_movement;
    switch (block->get_id()) {
        case ID_NORMAL:
            type_allows_movement = dynamic_cast<BlockNormal*>(block)->type_allows_movement(direction);
            break;
        case ID_U_DIR:
        case ID_R_DIR:
        case ID_D_DIR:
        case ID_L_DIR:
            type_allows_movement = dynamic_cast<BlockDirectional*>(block)->type_allows_movement(direction);
            break;
        case ID_ROTATE_0:
        case ID_ROTATE_1:
        case ID_ROTATE_2:
        case ID_ROTATE_3:
            type_allows_movement = dynamic_cast<BlockRotating*>(block)->type_allows_movement(direction);
            break;
        default:break;
    }
    return type_allows_movement
       && !block->is_move_restricted();
}

/**@return if a block can be removed*/
bool GameLogic::can_move_block(Block * block, char direction) {
    return block_allows_movement(block, direction)
       && !path_blocked(block, direction)
       && !tabs_impede(block, direction);
}

bool GameLogic::can_potentially_move_block(Block * block, char direction) {
    return block_allows_movement(block, direction)
       && !path_blocked(block, direction)
       && !tabs_always_impede(block, direction);
}

/**Determines if a block can be removed in any way*/
bool GameLogic::can_be_removed(Block * block) {
    return can_move_block(block, U_DIR) || can_move_block(block, D_DIR) || can_move_block(block, L_DIR) || can_move_block(block, R_DIR);
}

/**Determines if a block can be removed in any way*/
bool GameLogic::can_be_removed(int x, int y) {
    return can_be_removed(get_block(x, y));
}

/**Determines if a block can be removed, including if it and nearby rotateable blocks are rotated etc.*/
bool GameLogic::potentially_removable(Block * block) {
    return can_potentially_move_block(block, U_DIR)
        || can_potentially_move_block(block, D_DIR)
        || can_potentially_move_block(block, L_DIR)
        || can_potentially_move_block(block, R_DIR);
}

/**Determines if a block can be removed, including if it and nearby rotateable blocks are rotated etc.*/
bool GameLogic::potentially_removable(int x, int y) {
    return potentially_removable(get_block(x, y));
}

/**prints all removable block locations to the terminal*/
void GameLogic::print_removable() {
    for (int y=0; y<get_board_height(); y++) {
        for (int x=0; x<get_board_width(); x++) {
            if (board->block_exists(x, y) && potentially_removable(x, y)) {
                std::cout << "removable at " << x << "," << y << std::endl;
                return;
            }
        }
    }
}

/**takes one valid move and returns the block location */
sf::Vector2i GameLogic::get_hint() {//TODO fix how this breaks encapsulation
    for (int y=0; y<get_board_height(); y++) {
        for (int x=0; x<get_board_width(); x++) {
            if (board->block_exists(x, y) && potentially_removable(x, y)) {
                sf::Vector2i hint(x,y);
                return hint;
            }
        }
    }
}


/**Determines if block can be moved*/
bool GameLogic::can_move(int block_x, int block_y, char direction) {
    if (!block_exists(block_x, block_y)) {return true;}//TODO figure out what to do with this case
    return can_move_block(get_block(block_x, block_y), direction);
}

/**Attempts to move a block*/
bool GameLogic::try_move(int x, int y, char direction) {
    if (block_exists(x, y)) {
        bool valid_move = can_move(x, y, direction);
        if (valid_move) {remove_block(x, y);}
        else {add_wrong_move();}
        return valid_move;
    }
}

/**@return if a block is rotated on tap*/
//TODO remove hard coded string
bool GameLogic::tap_selected() {
    if (block_exists(selected_x, selected_y)) {
        Block * block = get_block(selected_x, selected_y);
        switch (block->get_id()) {
            case ID_ROTATE_0:
            case ID_ROTATE_1:
            case ID_ROTATE_2:
            case ID_ROTATE_3: {
                auto * casted_block = dynamic_cast<BlockRotating*>(block);
                if (!casted_block->is_move_restricted()) {
                    casted_block->rotate();
                    std::cout << "Rotated block at " << selected_x << ", " << selected_y << "\n";
                    return true;
                };
            }
            default: break;
        }
    }
    return false;
}

/**set the board size created by generator*/
void GameLogic::set_generated_board_size(int x, int y) {
    this->generated_board_x = x;
    this->generated_board_y = y;
}

/**set how many blocks of each type*/
void GameLogic::set_nums_of_blocks(std::string nums_of_nor, std::string nums_of_rot, std::string nums_of_dir) {
    this->nums_of_nor = nums_of_nor;
    this->nums_of_rot = nums_of_rot;
    this->nums_of_dir = nums_of_dir;
}

/**Attempts to move the selected block*/
bool GameLogic::try_move_selected(char direction) {return try_move(selected_x, selected_y, direction);}

/**Adds to wrong move counter*/
void GameLogic::add_wrong_move() {state->add_wrong_move();}

/**@return if a given block is move restricted*/
bool GameLogic::block_is_move_restricted(int x, int y) {return get_block(x, y)->is_move_restricted();}

/**@return if selected block is move restricted*/
bool GameLogic::selected_block_is_move_restricted() {return block_is_move_restricted(selected_x, selected_y);}

/**@return maximum level the player has reached*/
int GameLogic::get_max_level() {return state->get_max_level();}

/**@return current level*/
int GameLogic::get_cur_level() {return state->get_cur_level();}

/**Sets current level*/
void GameLogic::set_cur_level(int lvl) {state->set_cur_level(lvl);}

/**Adds 1 to current level*/
void GameLogic::increment_cur_level() {state->increment_cur_level();}

/**get the board x created by generator*/
int GameLogic::get_generated_board_x() {return generated_board_x;}

/**get the board y created by generator*/
int GameLogic::get_generated_board_y() {return generated_board_y;}

/** get nums of directional blocks*/
std::string GameLogic::get_nums_of_dir() {return nums_of_dir;}

/** get nums of rotating blocks*/
std::string GameLogic::get_nums_of_rot() {return nums_of_rot;}

/** get nums of normal blocks*/
std::string GameLogic::get_nums_of_nor() {return nums_of_nor;}
