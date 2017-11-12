//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameLogic.h"
#include "GameBoard.hpp"


void GameLogic::set_GameBoard(GameBoard &board) {this->board = &board;}

/**@return x index of selected block*/
int GameLogic::get_selected_x() {return selected_x;}

/**@return y index of selected block*/
int GameLogic::get_selected_y() {return selected_y;}

/**
  Sets postion of selected block_shape
  @param x index of selected block
  @param y index of selected block
*/
void GameLogic::set_selected_position(int x, int y) {
    selected_x = x;
    selected_y = y;
}

/**@return board width*/
int GameLogic::get_board_width() {return board->get_width();}

/**@return board height*/
int GameLogic::get_board_height() {return board->get_height();}

int GameLogic::is_valid_x(int x) {return x>=0 && x<get_board_width();}

int GameLogic::is_valid_y(int y) {return y>=0 && y<get_board_height();}

int GameLogic::is_valid_location(int x, int y) {return is_valid_x(x) && is_valid_y(y);}

//TODO why should the selected block ever be invalid? should just check validity when setting.
int GameLogic::is_selected_location_valid() {return is_valid_location(selected_x, selected_y);}

/**@return block type integer*/
int GameLogic::get_block(int x, int y) {return board->get_block(x, y);}

/**@return selected block*/
int GameLogic::get_selected_block() {
    if (is_selected_location_valid()) {return get_block(selected_x, selected_y);}
    else {return 0;}
}

/**
  Checks for collisions
  @param current block
  @param direction
  @return bool indicating whether there was a collision
*/
bool GameLogic::detect_collision (int x, int y, std::string direction) {
    if (direction == "up") {
        for (int y2 = y+1; y2<get_board_height(); y2++) {
            if (get_block(x, y2) != 0) {
                return true;
            }
        }
    } else if (direction == "down") {
        for (int y2 = y-1; y2>=0; y2--) {
            if (get_block(x, y2) != 0) {
                return true;
            }
        }
    } else if (direction == "left") {
        for (int x2 = x-1; x2>=0; x2--) {
            if (get_block(x2, y) != 0) {
                return true;
            }
        }
    } else if (direction == "right") {
        for (int x2 = x+1; x2<get_board_width(); x2++) {
            if (get_block(x2, y) != 0) {
                return true;
            }
        }
    }
    return false;
}

bool GameLogic::path_blocked(int x, int y, std::string direction) {
    //TODO rename the main function later.
    return detect_collision(x, y, direction);
}


/**
  Removes block
  @param x
  @param y
*/
void GameLogic::remove_block(int x, int y) {
    std::cout << "Removed block at " << x << ", " << y << "\n";
    board->remove_block(x, y);
    set_selected_position(-1, -1);
}


bool GameLogic::can_move(int block_x, int block_y, std::string direction) {
    //Block block = get_block(block_x, block_y);//assumes one is there
    //return block.type_allows_movement(direction) && !path_blocked(block_x, block_y, direction);
    int block = get_block(block_x, block_y);
    if (block == 0) {return true;}//TODO figure out what to do with this case
    if (path_blocked(block_x, block_y, direction)) {return false;}
    if (block == 10) {return true;}
    if (direction == "up") {
        if (block == 20) {return true;}
    } else if (direction == "right") {
        if (block == 21) {return true;}
    } else if (direction == "down") {
        if (block == 22) {return true;}
    } else if (direction == "left") {
        if (block == 23) {return true;}
    }
    return false;
}

/**
  Attempts to move blocks
  @param dir for move direction
*/
void GameLogic::try_move_any(int x, int y, std::string direction) {
    if (get_selected_block() != 0) {
        if (can_move(x, y, direction)) {
            remove_block(x, y);
        }
    }
}

void GameLogic::try_move_selected(std::string direction) {try_move_any(selected_x, selected_y, direction);}

//TODO remove after renaming usages
void GameLogic::try_move(std::string direction) {try_move_selected(direction);}

