//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameLogic.h"
#include <iostream>
#include <string.h>

/**
  Sets the board
  Temporary implementation; sets a very specific board.
*/
void GameLogic::init() {
    for (int x=0; x<get_board_width(); x++) {
        for (int y=0; y<get_board_height(); y++) {
            if (y%5 == 0) {board_array[x][y] = 10;}
            else {board_array[x][y] = 20+(y%4);}
        }
    }
}


/**
  Sets x index of selected block
  @param x index of selected block
*/
void GameLogic::set_selected_x(int x) {selected_x = x;}

/**
  Sets y index of selected block
  @param y index of selected block
*/
void GameLogic::set_selected_y(int y) {selected_y = y;}

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
    set_selected_x(x);
    set_selected_y(y);
}


/**@return board width*/
int GameLogic::get_board_width() {return board_width;}

/**@return board_height*/
int GameLogic::get_board_height() {return board_height;}

int GameLogic::is_valid_x(int x) {return x>=0 && x<get_board_width();}

int GameLogic::is_valid_y(int y) {return y>=0 && y<get_board_height();}

int GameLogic::is_valid_location(int x, int y) {return is_valid_x(x) && is_valid_y(y);}

//TODO why should the selected block ever be invalid? should just check validity when setting.
int GameLogic::is_selected_location_valid() {return is_valid_location(selected_x, selected_y);}

/**@return block type integer*/
int GameLogic::get_block(int x, int y) {return board_array[x][y];}


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
        for (int y2 = y+1; y2<board_height; y2++) {
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
        for (int x2 = x+1; x2<board_width; x2++) {
            if (get_block(x2, y) != 0) {
                return true;
            }
        }
    }
    return false;
}


/**
  Removes block
  @param x
  @param y
*/
void GameLogic::remove_block(int x, int y) {
    std::cout << "Removed block at " << x << ", " << y << "\n";
    board_array[x][y] = 0;
    set_selected_position(-1, -1);
}


/**
  Attempts to move blocks
  @param dir for move direction
*/
void GameLogic::try_move(std::string dir) {
    int x = selected_x;
    int y = selected_y;
    if (get_selected_block() != 0) {//TODO refactor all of this
        if (dir == "up") {
            if ((get_block(x, y) == 10 || get_block(x, y) == 20) && !detect_collision(x, y, "up")) {
                remove_block(x, y);
            }
        } else if (dir == "right") {
            if ((get_block(x, y) == 10 || get_block(x, y) == 21) && !detect_collision(x, y, "right")) {
                remove_block(x, y);
            }
        } else if (dir == "down") {
            if ((get_block(x, y) == 10 || get_block(x, y) == 22) && !detect_collision(x, y, "down")) {
                remove_block(x, y);
            }
        } else if (dir == "left") {
            if ((get_block(x, y) == 10 || get_block(x, y) == 23) && !detect_collision(x, y, "left")) {
                remove_block(x, y);
            }
        }
    }
}
