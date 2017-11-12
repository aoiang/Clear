//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include "GameBoard.hpp"

/**
  Sets board dimensions
  @param w for width
  @param h for height
*/
void GameBoard::init(int w, int h) {
    this->width = w;
    this->height = h;
    for(int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {this->board[x][y] = 0;}
    }
}

/**Initializes board*/
void GameBoard::init() {init(10, 10);}

/**
  Removes element from board
  @param x coordinate to remove
  @param y coordinate to remove
  @return bool to indicate successful removal
*/
bool GameBoard::remove(int x, int y) {
    if (x>this->width || y>this->height) {return false;}//doesn't handle if they're negative though.
    else {this->board[x][y] = 0;}
    return true;
}

/**
  Adds element to board
  @param x coordinate to add to
  @param y coordinate to add to
  @return bool to indicate successful addition
*/
bool GameBoard::add_block(int x, int y, int block) {
    //doesn't check for invalid position; unlike remove.
    if (board[x][y] != 0) {return false;}
    else {board[x][y] = block;}
    return true;
}

/**
  gets block on the board
  @param x coordinate to look at
  @param y coordinate to look at
  @return block desired
*/
 int GameBoard::get_block(int x, int y) {
    return board[x][y];
}
