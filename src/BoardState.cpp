#include "BoardState.hpp"
#include "Block.hpp"

/**
  Sets board dimensions
  @param w for width
  @param h for height
*/
void BoardState::init(int w, int h) {
    this->width = w;
    this->height = h;
}

/**Initializes board*/
void BoardState::init() {init(default_width, default_height);}

/**@return board width*/
int BoardState::get_board_width() {return width;}

/**@return board height*/
int BoardState::get_board_height() {return height;}

/**Checks if x coordinate exists on the board*/
int BoardState::is_valid_x(int x) {return x>=0 && x<get_board_width();}

/**Checks if y coordinate exists on the board*/
int BoardState::is_valid_y(int y) {return y>=0 && y<get_board_height();}

/**Checks if x, y position exists on the board*/
int BoardState::is_valid_location(int x, int y) {return is_valid_x(x) && is_valid_y(y);}

/**
  Removes element from board
  @param x coordinate to remove
  @param y coordinate to remove
  @return bool to indicate successful removal
*/
bool BoardState::remove_block(int x, int y) {
    if (x>width || y>height) {return false;}//doesn't handle if they're negative though.
    else {board[x][y] = nullptr;}
    block_removed_ct ++;
    if (block_removed_ct == block_ct) {
        std::cout << std::endl << "Board is clear" << std::endl << std::endl;
        is_clear = true;
    }
    return true;
}

/**
  Adds Block to board
  @return bool to indicate successful addition
*/
bool BoardState::add_block(Block * block) {
    //doesn't check for invalid position; unlike remove.
    int x = block->get_x();
    int y = block->get_y();
    if (board[x][y] != nullptr) {return false;}
    else {board[x][y] = block;}
    block_ct ++;
    return true;
}

/**
  Gets Block from the board
  @param x coordinate
  @param y coordinate
  @return Block desired
*/
Block * BoardState::get_block(int x, int y) {return board[x][y];}

/**Checks if block exists at index*/
bool BoardState::block_exists(int x, int y) {return is_valid_location(x,y) && board[x][y]!=nullptr;}

/**Checks if the board is empty*/
bool BoardState::get_is_clear() {return is_clear;}

/**Adds a wrong move to the board*/
void BoardState::add_wrong_move() {
    wrong_moves++;
    std::cout << "Wrong move; " << wrong_moves << " total" << std::endl;
}

/**@return number of blocks removed*/
int BoardState::get_blocks_removed_ct() {return block_removed_ct;}
