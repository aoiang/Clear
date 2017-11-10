//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameLogic.h"
#include <iostream>

/**
  Sets the board
*/
void GameLogic::init() {
    for (int i = 0; i < get_board_width(); i++) {
        for (int j = 0; j < get_board_height(); j++) {
            board_array[0][j] = 20 + (j % 4);
        }
    }
}


/**
  Sets column index of selected block
  @param col index of selected block
*/
void GameLogic::set_selected_col(int col) {
    selected_col = col;
}


/**
  Gets column index of selected block
  @return col index of selected block
*/
int GameLogic::get_selected_col() {
    return selected_col;
}


/**
  Sets row index of selected block
  @param row index of selected block
*/
void GameLogic::set_selected_row(int row) {
    selected_row = row;
}


/**
  Gets row index of selected block
  @return row index of selected block
*/
int GameLogic::get_selected_row() {
    return selected_row;
}


/**
  Sets postion of selected block_shape
  @param col index of selected block
  @param row index of selected block
*/
void GameLogic::set_selected_position(int row, int col) {
    selected_row = row;
    selected_col = col;
}


/**
  @return board width
*/
int GameLogic::get_board_width() {
    return board_width;
}

int GameLogic::get_board_height() {
    return board_height;
}


int GameLogic::get_block(int x, int y) {
    return board_array[x][y];
}


/**
  Checks for collisions
  @param current block
  @param direction
  @return bool indicating whether there was a collision
*/
bool GameLogic::collision_detector (int current_block_row, int current_block_col, std::string direction) {
    // if(direction == "up"){
    //     for(int i=0; i < get_board_width(); i++){
    //         if(get_block(0, i).get_row() == current_block.get_row()){
    //             if(get_block(0, i).get_col() < current_block.get_col()){
    //                 if(get_block(0, i).get_row() > 0 && get_block(0, i).get_row() < 600 && get_block(0, i).get_col() > 0 && get_block(0, i).get_col() < 800){
    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    // }
    // if(direction == "down"){
    //     for(int i=0; i < get_board_width(); i++){
    //         if(get_block(0, i).get_row() == current_block.get_row()){
    //             if(get_block(0, i).get_col()> current_block.get_col()){
    //                 if(get_block(0, i).get_row() > 0 && get_block(0, i).get_row() < 600 && get_block(0, i).get_col() > 0 && get_block(0, i).get_col() < 800){
    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    // }
    // if(direction == "left"){
    //     for(int i=0; i < get_board_width(); i++){
    //         if(get_block(0, i).get_col() == current_block.get_col()){
    //             if(get_block(0, i).get_row() < current_block.get_row()){
    //                 if(get_block(0, i).get_row() > 0 && get_block(0, i).get_row() < 600 && get_block(0, i).get_col() > 0 && get_block(0, i).get_col() < 800){
    //                     return true;
    //                 }
    //
    //             }
    //         }
    //     }
    // }
    // if(direction == "right"){
    //     for(int i=0; i < get_board_width(); i++){
    //         if(get_block(0, i).get_col() == current_block.get_col()){
    //             if(get_block(0, i).get_row() > current_block.get_row()){
    //                 if(get_block(0, i).get_row() > 0 && get_block(0, i).get_row() < 600 && get_block(0, i).get_col() > 0 && get_block(0, i).get_col() < 800){
    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    // }
    return false;
}


/**
  Attempts to move blocks
  @param dir for move direction
*/
void GameLogic::try_move(std::string dir) {
    int i = selected_row;
    int j = selected_col;
    if (i != -1) {
        if (dir == "up") {
            if ((get_block(i, j) == 10 || get_block(i, j) == 20) && !collision_detector(i, j, "up")) {
                std::cout << "Removed block at " << i << ", " << j << "\n";
                board_array[i][j] = 0;
                set_selected_position(-1, -1);
            }
        }
    }
    //     else if (dir == "down") {
    //         if (get_block(0, i).get_direction() == "down" && !collision_detector(get_block(0, i), get_block(0, i).get_direction())) {
    //             board_array[0][j] = 0;
    //         }
    //         if (!get_block(0, i).get_has_direction() && !collision_detector(get_block(0, i), "down")) {
    //             board_array[0][j] = 0;
    //         }
    //     }
    //     if (dir == "left") {
    //         if (get_block(0, i).get_direction() == "left" && !collision_detector(get_block(0, i), get_block(0, i).get_direction())) {
    //             board_array[0][j] = 0;
    //         }
    //         if (!get_block(0, i).get_has_direction() && !collision_detector(get_block(0, i), "left")) {
    //             board_array[0][j] = 0;
    //         }
    //     }
    //     if (dir == "right") {
    //         if (get_block(0, i).get_direction() == "right" && !collision_detector(get_block(0, i), get_block(0, i).get_direction())) {
    //             board_array[0][j] = 0;
    //         }
    //         if (!get_block(0, i).get_has_direction() && !collision_detector(get_block(0, i), "right")) {
    //             board_array[0][j] = 0;
    //         }
    //     }
    // }
}
