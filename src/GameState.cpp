//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameState.h"


/**
* Sets the board
*/
void GameState::init() {
  for(int i=0; i<5; i++){
      board_array[i].init(i);
      board_array[i].setPosition(100+80*i, 200);
  }
}


/**
* @return the board array
*/
Normal_Block* GameState::get_board_array() {
    return board_array;
}

/**
* Sets the board array
* @param board_array
*/
void GameState::set_board_array(Normal_Block * board_array) {
    for(int i =0; i<5; i++){
        this -> board_array[i] = board_array[i];
    }
}

/**
* Checks for collisions
* @param current block
* @param direction
* @return bool indicating whether there was a collision
*/
bool GameState::collision_detector(Normal_Block current_block, std::string direction) {
    if(direction == "up"){
        for(int i=0; i < 5; i++){
            if(board_array[i].getX() == current_block.getX()){
                if(board_array[i].getY() < current_block.getY()){
                    if(board_array[i].getX() > 0 && board_array[i].getX() < 800 && board_array[i].getY() > 0 && board_array[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "down"){
        for(int i=0; i < 5; i++){
            if(board_array[i].getX() == current_block.getX()){
                if(board_array[i].getY()> current_block.getY()){
                    if(board_array[i].getX() > 0 && board_array[i].getX() < 800 && board_array[i].getY() > 0 && board_array[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "left"){
        for(int i=0; i < 5; i++){
            if(board_array[i].getY() == current_block.getY()){
                if(board_array[i].getX() < current_block.getX()){
                    if(board_array[i].getX() > 0 && board_array[i].getX() < 800 && board_array[i].getY() > 0 && board_array[i].getY() < 600){
                        return true;
                    }

                }
            }
        }
    }
    if(direction == "right"){
        for(int i=0; i < 5; i++){
            if(board_array[i].getY() == current_block.getY()){
                if(board_array[i].getX() > current_block.getX()){
                    if(board_array[i].getX() > 0 && board_array[i].getX() < 800 && board_array[i].getY() > 0 && board_array[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
* Attempts to move blocks
* @param dir for move direction
*/
void GameState::try_move(std::string dir) {
    for(int i = 0; i < 5; i++) {
        if (board_array[i].get_selected()) {
            if(dir == "up") {
                if(board_array[i].get_direction() == "up" && !collision_detector(board_array[i], board_array[i].get_direction())){
                    board_array[i].move(0.0,  -10);
                }
                if(!board_array[i].get_has_direction() && !collision_detector(board_array[i], "up")){
                    board_array[i].move(0.0,  -10);
                }
            }
            if(dir == "down"){
                if(board_array[i].get_direction() == "down" && !collision_detector(board_array[i], board_array[i].get_direction())){
                    board_array[i].move(0.0,  10);
                }
                if(!board_array[i].get_has_direction() && !collision_detector(board_array[i], "down")){
                    board_array[i].move(0.0,  10);
                }
            }
            if(dir == "left"){
                if(board_array[i].get_direction() == "left" && !collision_detector(board_array[i], board_array[i].get_direction())){
                    board_array[i].move(-10,  0);
                }
                if(!board_array[i].get_has_direction() && !collision_detector(board_array[i], "left")){
                    board_array[i].move(-10,  0);
                }
            }
            if(dir == "right"){
                if(board_array[i].get_direction() == "right" && !collision_detector(board_array[i], board_array[i].get_direction())){
                    board_array[i].move(10,  0);
                }
                if(!board_array[i].get_has_direction() && !collision_detector(board_array[i], "right")){
                    board_array[i].move(10,  0);
                }
            }
        }
    }
}
