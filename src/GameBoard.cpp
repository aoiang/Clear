//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include "GameBoard.hpp"
#include "Block.h"
#include "Normal_Block.h"
#include "Directional_Block.h"

/**
  Sets board dimensions
  @param w for width
  @param h for height
*/
void GameBoard::init(int w, int h) {
    this->width = w;
    this->height = h;
    for(int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            //TODO need way to delete these objects. put that in the remove?
            Block * block;
            if (y%5 == 0) {
                block = new Normal_Block(x,y);
            } else {
                block = new Directional_Block(x,y,y%4);
            }
            add_block(block);
        }
        std::cout << "\n";
    }
}

/**Initializes board*/
void GameBoard::init() {init(default_width, default_height);}


/**@return board width*/
int GameBoard::get_board_width() {return width;}

/**@return board height*/
int GameBoard::get_board_height() {return height;}

int GameBoard::is_valid_x(int x) {return x>=0 && x<get_board_width();}

int GameBoard::is_valid_y(int y) {return y>=0 && y<get_board_height();}

int GameBoard::is_valid_location(int x, int y) {return is_valid_x(x) && is_valid_y(y);}


/**
  Removes element from board
  @param x coordinate to remove
  @param y coordinate to remove
  @return bool to indicate successful removal
*/
bool GameBoard::remove_block(int x, int y) {
    if (x>width || y>height) {return false;}//doesn't handle if they're negative though.
    else {board[x][y] = nullptr;}
    return true;
}

/**
  Adds element to board
  @param x coordinate to add to
  @param y coordinate to add to
  @return bool to indicate successful addition
*/
bool GameBoard::add_block(Block * block) {
    //doesn't check for invalid position; unlike remove.
    int x = block->get_x();
    int y = block->get_y();
    if (board[x][y] != nullptr) {return false;}
    else {board[x][y] = block;}
    return true;
}

/**
  gets block on the board
  @param x coordinate to look at
  @param y coordinate to look at
  @return block desired
*/
Block * GameBoard::get_block(int x, int y) {
    return board[x][y];
}

bool GameBoard::block_exists(int x, int y) {
    return is_valid_location(x,y) && board[x][y]!=nullptr;
}
