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
    for (int i=0; i<get_board_width(); i++) {
        for (int j=0; j<get_board_height(); j++) {
            if (j%5 == 0) {board_array[i][j] = 10;}
            else {board_array[i][j] = 20+(j%4);}
        }
    }
}


/**
  Sets column index of selected block
  @param col index of selected block
*/
void GameLogic::set_selected_col(int col) {selected_col = col;}

/**
  Sets row index of selected block
  @param row index of selected block
*/
void GameLogic::set_selected_row(int row) {selected_row = row;}

/**@return col index of selected block*/
int GameLogic::get_selected_col() {return selected_col;}

/**@return row index of selected block*/
int GameLogic::get_selected_row() {return selected_row;}


/**
  Sets postion of selected block_shape
  @param col index of selected block
  @param row index of selected block
*/
void GameLogic::set_selected_position(int row, int col) {
    set_selected_row(row);
    set_selected_col(col);
}


/**@return board width*/
int GameLogic::get_board_width() {return board_width;}

/**@return board_height*/
int GameLogic::get_board_height() {return board_height;}

int GameLogic::is_valid_row(int row) {return row>=0 && row<get_board_height();}

int GameLogic::is_valid_col(int col) {return col>=0 && col<get_board_width();}

int GameLogic::is_valid_location(int x, int y) {return is_valid_col(x) && is_valid_row(y);}

//TODO why should the selected block ever be invalid? should just check validity when setting.
int GameLogic::is_selected_location_valid() {return is_valid_location(selected_col, selected_row);}

/**@return block type integer*/
int GameLogic::get_block(int x, int y) {return board_array[x][y];}


/**@return selected block*/
int GameLogic::get_selected_block() {
    if (is_selected_location_valid()) {return get_block(selected_col, selected_row);}
    else {return 0;}
}

/**
  Checks for collisions
  @param current block
  @param direction
  @return bool indicating whether there was a collision
*/
bool GameLogic::detect_collision (int row, int col, std::string direction) {
    if (direction == "up") {
        for (int i = row-1; i>=0; i--) {
            if (get_block(i, col) != 0) {
                return true;
            }
        }
    } else if (direction == "down") {
        for (int i = row+1; i<board_height; i++) {
            if (get_block(i, col) != 0) {
                return true;
            }
        }
    } else if (direction == "left") {
        for (int j = col-1; j>=0; j--) {
            if (get_block(row, j) != 0) {
                return true;
            }
        }
    } else if (direction == "right") {
        for (int j = col+1; j<board_width; j++) {
            if (get_block(row, j) != 0) {
                return true;
            }
        }
    }
    return false;
}


/**
  Removes block
  @param row
  @param col
*/
void GameLogic::remove_block(int row, int col) {
    std::cout << "Removed block at " << row << ", " << col << "\n";
    board_array[row][col] = 0;
    set_selected_position(-1, -1);
}


/**
  Attempts to move blocks
  @param dir for move direction
*/
void GameLogic::try_move(std::string dir) {
    int row = selected_row;
    int col = selected_col;
    if (get_selected_block() != 0) {//TODO refactor all of this
        if (dir == "up") {
            if ((get_block(row, col) == 10 || get_block(row, col) == 20) && !detect_collision(row, col, "up")) {
                remove_block(row, col);
            }
        } else if (dir == "right") {
            if ((get_block(row, col) == 10 || get_block(row, col) == 21) && !detect_collision(row, col, "right")) {
                remove_block(row, col);
            }
        } else if (dir == "down") {
            if ((get_block(row, col) == 10 || get_block(row, col) == 22) && !detect_collision(row, col, "down")) {
                remove_block(row, col);
            }
        } else if (dir == "left") {
            if ((get_block(row, col) == 10 || get_block(row, col) == 23) && !detect_collision(row, col, "left")) {
                remove_block(row, col);
            }
        }
    }
}
