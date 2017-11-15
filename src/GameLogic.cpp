//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameLogic.hpp"

/**Sets GameBoard*/
void GameLogic::set_GameBoard(GameBoard &board) {this->board = &board;}

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

    if (direction == 'u' || direction == 'd') {
        if (   (get_block(x, y)->get_tab('l') && block_exists(x-1, y))
            || (get_block(x, y)->get_tab('r') && block_exists(x+1, y))
            || (block_exists(x-1, y) && get_block(x-1, y)->get_tab('r'))
            || (block_exists(x+1, y) && get_block(x+1, y)->get_tab('l'))) {
            return true;
        }
    } else if (direction == 'l' || direction == 'r') {
        if (   (get_block(x, y)->get_tab('u') && block_exists(x, y+1))
            || (get_block(x, y)->get_tab('d') && block_exists(x, y-1))
            || (block_exists(x, y+1) && get_block(x, y+1)->get_tab('d'))
            || (block_exists(x, y-1) && get_block(x, y-1)->get_tab('u'))) {
            return true;
        }
    }
    return false;
}

/**Checks if a direction relative to a block is clear or blocked.*/
bool GameLogic::path_blocked(Block * block, char direction) {
    int x = block->get_x();
    int y = block->get_y();

    if (direction == 'u') {
        for (int y2 = y+1; y2<get_board_height(); y2++) {
            if (block_exists(x, y2)) {
                return true;
            }
        }
    } else if (direction == 'd') {
        for (int y2 = y-1; y2>=0; y2--) {
            if (block_exists(x, y2)) {
                return true;
            }
        }
    } else if (direction == 'l') {
        for (int x2 = x-1; x2>=0; x2--) {
            if (block_exists(x2, y)) {
                return true;
            }
        }
    } else if (direction == 'r') {
        for (int x2 = x+1; x2<get_board_width(); x2++) {
            if (block_exists(x2, y)) {
                return true;
            }
        }
    }
    return false;
}

bool GameLogic::path_blocked(int x, int y, char direction) {
    return path_blocked(get_block(x,y), direction);
}


/**Removes block*/
void GameLogic::remove_block(int x, int y) {
    std::cout << "Removed block at " << x << ", " << y << "\n";
    board->remove_block(x, y);
    set_selected_position(-1, -1);
}


bool GameLogic::can_move_block(Block * block, char direction) {
    switch (block->get_id()) {
        case 10:
            return static_cast<Normal_Block*>(block)->type_allows_movement(direction) && !path_blocked(block, direction) && !tabs_impede(block, direction);
        case 20:
        case 21:
        case 22:
        case 23:
            return static_cast<Directional_Block*>(block)->type_allows_movement(direction) && !path_blocked(block, direction) && !tabs_impede(block, direction);
    }
}

bool GameLogic::can_be_removed(Block * block) {
    return can_move_block(block, 'u') || can_move_block(block, 'd') || can_move_block(block, 'l') || can_move_block(block, 'r');
}

/**Determines if block can be moved*/
bool GameLogic::can_move(int block_x, int block_y, char direction) {
    if (!block_exists(block_x, block_y)) {return true;}//TODO figure out what to do with this case
    can_move_block(get_block(block_x, block_y), direction);
}

/**Attempts to move a block*/
void GameLogic::try_move(int x, int y, char direction) {
    if (block_exists(x, y)) {
        if (can_move(x, y, direction)) {
            remove_block(x, y);
        }
    }
}

/**Attempts to move the selected block*/
void GameLogic::try_move_selected(char direction) {try_move(selected_x, selected_y, direction);}
