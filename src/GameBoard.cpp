#include "GameBoard.hpp"
#include "Block.hpp"
#include "Normal_Block.hpp"
#include "Directional_Block.hpp"
#include "Rotating_Block.hpp"
#include "Generator.h"


/**
  Sets board dimensions, adds Blocks
  @param w for width
  @param h for height
*/
void GameBoard::init(int w, int h) {
    Generator generated_board;
    generated_board.board_generator(1);
    this->width = w;
    this->height = h;
    for(int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            //TODO need way to delete these objects. put that in the remove?
            printf("%d,%d\n", generated_board.board[x][y].direction, generated_board.board[x][y].block_rotation);
            Block * block;
            if (generated_board.board[x][y].exist == 1){
                if (generated_board.board[x][y].direction != 0){
                    switch (generated_board.board[x][y].direction){
                        case 1:{
                            block = new Directional_Block(x, y, 0);
                            add_block(block);
                        }
                        case 2:{
                            block = new Directional_Block(x, y, 1);
                            add_block(block);
                        }
                        case 3:{
                            block = new Directional_Block(x, y, 2);
                            add_block(block);
                        }
                        case 4:{
                            block = new Directional_Block(x, y, 3);
                            add_block(block);
                        }
                        default: break;
                    }
                }
                if (generated_board.board[x][y].block_rotation == 1){
                    block = new Rotating_Block(x, y);
                    for (int i = 0; i <=3; i++){
                        if (generated_board.board[x][y].tab[i] == 1){
                            switch(i){
                                case 0: block->set_tab('u', true);
                                case 1: block->set_tab('d', true);
                                case 2: block->set_tab('l', true);
                                case 3: block->set_tab('r', true);
                                default:break;
                            }
                        }
                    }
                    add_block(block);
                }

                if (generated_board.board[x][y].block_rotation != 1 && generated_board.board[x][y].direction != 1){
                    block = new Directional_Block(x, y, 4);
                    add_block(block);

                }

            }

//            if (y%5 == 0) {
//                block = new Rotating_Block(x, y);
//                // block = new Normal_Block(x, y);
//                // tabs set here
//                block->set_tab('u', true);
//                block->set_tab('r', true);
//                // block->set_tab('d', true);
//                // block->set_tab('l', true);
//                add_block(block);
//
//            } else if ((x+y)%3) {
//              block = new Directional_Block(x, y, y%4);
//              add_block(block);
//            }
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

/**Checks if x coordinate exists on the board*/
int GameBoard::is_valid_x(int x) {return x>=0 && x<get_board_width();}

/**Checks if y coordinate exists on the board*/
int GameBoard::is_valid_y(int y) {return y>=0 && y<get_board_height();}

/**Checks if x, y position exists on the board*/
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
  Adds Block to board
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
  Gets Block on the board
  @param x coordinate
  @param y coordinate
  @return Block desired
*/
Block * GameBoard::get_block(int x, int y) {
    return board[x][y];
}

/**Checks if block exists at index*/
bool GameBoard::block_exists(int x, int y) {
    return is_valid_location(x,y) && board[x][y]!=nullptr;
}
