#include "BoardState.hpp"
#include "Block.hpp"
#include "BlockNormal.hpp"
#include "BlockDirectional.hpp"
#include "BlockRotating.hpp"
#include <iostream>
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
    //old_import_board(filepath);
    import_board(filepath + ".new");
}

void BoardState::old_import_board(std::string filepath) {
    this->width = default_width;
    this->height = default_height;

    std::ifstream inFile(filepath);

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
    export_board(filepath + ".new");
}

void BoardState::import_board(std::string filepath) {
    std::ifstream level_file(filepath);
    
    std::string line;
    getline(level_file, line);
    this->width = stoi(line);
    getline(level_file, line);
    this->height = stoi(line);
    
    for (int y=0; y<height; y++) {
        getline(level_file, line);
        std::vector<std::string> blocks = Block::split_string(line, '\t');
        for (int x=0; x<width; x++) {
            if (blocks[x]!="") {
                add_block(Block::import_block(blocks[x], x, y));
            }
        }
    }
    level_file.close();
}

void BoardState::export_board(std::string filepath) {
    //width, height, and all of the blocks in an array.
    std::ofstream level_file;
    level_file.open(filepath);
    level_file << width <<"\n";
    level_file << height <<"\n";
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (block_exists(x, y)) {
                level_file << export_block(x, y);
            }
            level_file << "\t";
        }
        level_file << "\n";
    }
    level_file.close();
}

std::string BoardState::export_block(int x, int y) {
    return get_block(x, y)->get_identity();
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
