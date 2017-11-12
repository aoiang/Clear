//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include "GameBoard.hpp"

/**
  Sets board dimensions and populates board
  @param w for width
  @param h for height
*/
void GameBoard::init(int w, int h) {
    width = w;
    height = h;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (y%5 == 0) {board[x][y] = 10;}
            else {board[x][y] = 20+(y%4);}
        }
    }
}

/**Initializes the board with dimensions 10, 10*/
void GameBoard::init() {init(10, 10);}

/**@return width*/
int GameBoard::get_width() {return width;}

/**@return height*/
int GameBoard::get_height() {return height;}

/**
  Gets block on the board
  @param x coordinate to look at
  @param y coordinate to look at
  @return block desired
*/
 int GameBoard::get_block(int x, int y) {
    return board[x][y];
}

/**
  Removes element from board
  @param x coordinate to remove
  @param y coordinate to remove
*/
void GameBoard::remove_block(int x, int y) {
    board[x][y] = 0;
}
