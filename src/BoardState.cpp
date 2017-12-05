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
    //old_import_board(filepath);
    import_board(filepath);
    std::cout << "Level loaded from " << filepath << std::endl;
}

void BoardState::import_board(std::string filepath) {
    std::ifstream level_file(filepath);

    std::string line;
    getline(level_file, line);
    this->width = stoi(line);
    getline(level_file, line);
    this->height = stoi(line);

    for (int y=height-1; y>=0; y--) {
        getline(level_file, line);
        std::vector<std::string> blocks = Block::split_string(line, '\t');
        for (int x=0; x<width; x++) {
            if (!blocks[x].empty()) {
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
    if (!is_valid_location(x, y)) {std::cout << "bad remove request at " << x << "," << y << "\n";}
    else {board[x][y] = nullptr;}
    return (is_valid_location(x, y));
}

/**
  Adds Block to board
  @return bool to indicate successful addition
*/
bool BoardState::add_block(Block * block) {
    int x = block->get_x();
    int y = block->get_y();
    if (is_valid_location(x, y) && !block_exists(x, y)) {
        board[x][y] = block;
        return true;
    }
    std::cout << "bad add request at " << x << "," << y << "\n";
    return false;
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

bool BoardState::is_clear() {
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (block_exists(x, y)) {return false;}
        }
    }
    return true;
}
