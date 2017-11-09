//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameLogic.h"


/**
  Sets the board
*/
void GameLogic::init() {
    for(int i = 0; i < get_board_width(); i++){
        board_array[0][i].init(i);
        board_array[0][i].setPosition(i, 0);
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


Normal_Block GameLogic::get_block(int x, int y) {
    return board_array[x][y];
}


/**
  Checks for collisions
  @param current block
  @param direction
  @return bool indicating whether there was a collision
*/
bool GameLogic::collision_detector(Normal_Block current_block, std::string direction) {
    if(direction == "up"){
        for(int i=0; i < get_board_width(); i++){
            if(board_array[0][i].getX() == current_block.getX()){
                if(board_array[0][i].getY() < current_block.getY()){
                    if(board_array[0][i].getX() > 0 && board_array[0][i].getX() < 800 && board_array[0][i].getY() > 0 && board_array[0][i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "down"){
        for(int i=0; i < get_board_width(); i++){
            if(board_array[0][i].getX() == current_block.getX()){
                if(board_array[0][i].getY()> current_block.getY()){
                    if(board_array[0][i].getX() > 0 && board_array[0][i].getX() < 800 && board_array[0][i].getY() > 0 && board_array[0][i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "left"){
        for(int i=0; i < get_board_width(); i++){
            if(board_array[0][i].getY() == current_block.getY()){
                if(board_array[0][i].getX() < current_block.getX()){
                    if(board_array[0][i].getX() > 0 && board_array[0][i].getX() < 800 && board_array[0][i].getY() > 0 && board_array[0][i].getY() < 600){
                        return true;
                    }

                }
            }
        }
    }
    if(direction == "right"){
        for(int i=0; i < get_board_width(); i++){
            if(board_array[0][i].getY() == current_block.getY()){
                if(board_array[0][i].getX() > current_block.getX()){
                    if(board_array[0][i].getX() > 0 && board_array[0][i].getX() < 800 && board_array[0][i].getY() > 0 && board_array[0][i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


/**
  Attempts to move blocks
  @param dir for move direction
*/
void GameLogic::try_move(std::string dir) {
    int i = selected_col;
    if (i != -1) {
        if (dir == "up") {
            if (board_array[0][i].get_direction() == "up" && !collision_detector(board_array[0][i], board_array[0][i].get_direction())) {
                board_array[0][i].move(0.0,  -10);
            }
            if(!board_array[0][i].get_has_direction() && !collision_detector(board_array[0][i], "up")){
                board_array[0][i].move(0.0,  -10);
            }
        }
        else if (dir == "down") {
            if (board_array[0][i].get_direction() == "down" && !collision_detector(board_array[0][i], board_array[0][i].get_direction())) {
                board_array[0][i].move(0.0,  10);
            }
            if (!board_array[0][i].get_has_direction() && !collision_detector(board_array[0][i], "down")) {
                board_array[0][i].move(0.0,  10);
            }
        }
        if (dir == "left") {
            if (board_array[0][i].get_direction() == "left" && !collision_detector(board_array[0][i], board_array[0][i].get_direction())) {
                board_array[0][i].move(-10,  0);
            }
            if (!board_array[0][i].get_has_direction() && !collision_detector(board_array[0][i], "left")) {
                board_array[0][i].move(-10,  0);
            }
        }
        if (dir == "right") {
            if (board_array[0][i].get_direction() == "right" && !collision_detector(board_array[0][i], board_array[0][i].get_direction())) {
                board_array[0][i].move(10,  0);
            }
            if (!board_array[0][i].get_has_direction() && !collision_detector(board_array[0][i], "right")) {
                board_array[0][i].move(10,  0);
            }
        }
    }
}
