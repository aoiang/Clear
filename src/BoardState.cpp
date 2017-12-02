#include "BoardState.hpp"
#include "BlockNormal.hpp"
#include "BlockDirectional.hpp"
#include "BlockRotating.hpp"
#include <fstream>

/**
  Sets board dimensions
  @param w for width
  @param h for height
*/
BoardState::BoardState(int w, int h) {
    this->width = w;
    this->height = h;
}

/**Initializes board*/
BoardState::BoardState() {
    this->width = default_width;
    this->height = default_height;
}

/**Loads board from a file*/
BoardState::BoardState(std::string filepath) {
    this->width = default_width;
    this->height = default_height;

    std::ifstream inFile;
    inFile.open(filepath);

    int entry_ct = 0;
    int block_ct = 0;
    std::string entry;

    while(inFile >> entry) {
        if (entry != "0") {
            Block * block = nullptr;

            int x = entry_ct%default_width;
            int y = 8-(entry_ct/default_width);

            int direction = 0;
            switch (std::stoi(entry.substr(0, 2))) {
                case 10:
                    block = new BlockNormal(x, y);
                    break;
                case ID_L_DIR: direction++;
                case ID_D_DIR: direction++;
                case ID_R_DIR: direction++;
                case ID_U_DIR:
                    block = new BlockDirectional(x, y, direction);
                    break;
                case ID_ROTATE_0:
                    block = new BlockRotating(x, y);
                    break;
                default: break;
            }

            if (entry.substr(3, 1) == "1") {block->set_tab('u', true);}
            if (entry.substr(4, 1) == "1") {block->set_tab('r', true);}
            if (entry.substr(5, 1) == "1") {block->set_tab('d', true);}
            if (entry.substr(6, 1) == "1") {block->set_tab('l', true);}

            block->set_move_restriction(std::stoi(entry.substr(8, 2)));

            add_block(block);
        }
        entry_ct++;
    }
    std::cout << "Level loaded from " << filepath << std::endl;
    inFile.close();
}

void BoardState::export_board(std::string filepath) {
    //height, width, and all of the blocks in an array.
    //first two are h and w, then every one after is a block; everything on its own line.
}

unsigned long BoardState::export_block(int x, int y) {
    Block * block = get_block(x, y);
    return 0;
}


/**@return board width*/
int BoardState::get_board_width() {return width;}

/**@return board height*/
int BoardState::get_board_height() {return height;}

/**Checks if x coordinate exists on the board*/
bool BoardState::is_valid_x(int x) {return x>=0 && x<get_board_width();}

/**Checks if y coordinate exists on the board*/
bool BoardState::is_valid_y(int y) {return y>=0 && y<get_board_height();}

/**Checks if x, y position exists on the board*/
bool BoardState::is_valid_location(int x, int y) {return is_valid_x(x) && is_valid_y(y);}

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


void BoardState::print_board() {
    for (int y=0; y<get_board_height(); y++) {
        for (int x=0; x<get_board_width(); x++) {
            if (!block_exists(x,y)) {std::cout << true << " ";}
            else {std::cout << get_block(x,y)->get_id() << " ";}
        }
        std::cout<<"\n";
    }
}
