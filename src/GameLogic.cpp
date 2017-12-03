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
    int x = block->get_x();
    int y = block->get_y();

    switch (direction) {
        case U_DIR: case D_DIR:
            return block->get_tab(L_DIR) && block_exists(x-1, y)
                || block->get_tab(R_DIR) && block_exists(x+1, y)
                || block_exists(x-1, y) && get_block(x-1, y)->get_tab(R_DIR)
                || block_exists(x+1, y) && get_block(x+1, y)->get_tab(L_DIR);
        case L_DIR: case R_DIR:
            return block->get_tab(U_DIR) && block_exists(x, y+1)
                || block->get_tab(D_DIR) && block_exists(x, y-1)
                || block_exists(x, y+1) && get_block(x, y+1)->get_tab(D_DIR)
                || block_exists(x, y-1) && get_block(x, y-1)->get_tab(U_DIR);
        default:break;
    }
}

/**Checks if a direction relative to a block is clear or blocked.*/
bool GameLogic::path_blocked(Block * block, char direction) {
    int x = block->get_x();
    int y = block->get_y();

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

/**@return if a block's path is blocked*/
bool GameLogic::path_blocked(int x, int y, char direction) {
    return path_blocked(get_block(x,y), direction);
}

/**Removes block at index x,y*/
//TODO remove hard coded string
void GameLogic::remove_block(int x, int y) {
    std::cout << "Removed block at " << x << ", " << y << "\n";
    board->remove_block(x, y);
    state->increment_blocks_removed();
    set_selected_position(-1, -1);
    if (get_blocks_removed_ct() == board->get_block_ct()) {
        std::cout << std::endl << "Board is clear" << std::endl << std::endl;
        state->set_is_clear();
    }
}

/**@return if a block can be removed*/
bool GameLogic::can_move_block(Block * block, char direction) {
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
       && !block->is_move_restricted(get_blocks_removed_ct())
       && !path_blocked(block, direction)
       && !tabs_impede(block, direction);
}

/**Determines if a block can be removed in any way*/
bool GameLogic::can_be_removed(Block * block) {
    return can_move_block(block, U_DIR) || can_move_block(block, D_DIR) || can_move_block(block, L_DIR) || can_move_block(block, R_DIR);
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
                if (!casted_block->is_move_restricted(get_blocks_removed_ct())) {
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

/**Attempts to move the selected block*/
bool GameLogic::try_move_selected(char direction) {return try_move(selected_x, selected_y, direction);}

/**@return if the board has been cleared*/
bool GameLogic::get_is_clear() {return state->get_is_clear();}

/**Adds to wrong move counter*/
void GameLogic::add_wrong_move() {state->add_wrong_move();}

/**@return number of blocks removed from the board*/
int GameLogic::get_blocks_removed_ct() {return state->get_blocks_removed();}

/**@return if a given block is move restricted*/
bool GameLogic::block_is_move_restricted(int x, int y) {return get_block(x, y)->is_move_restricted(get_blocks_removed_ct());}

/**@return if selected block is move restricted*/
bool GameLogic::selected_block_is_move_restricted() {return block_is_move_restricted(selected_x, selected_y);}
