#include "GameState.hpp"

GameState::GameState(std::string) {}

GameState::GameState() {
  max_level = 0;
  cur_level = 1;
}

/**Reset current board variables*/
void GameState::init_current_board() {
    current_board_wrong_moves = 0;
    current_board_block_removed = 0;
    current_board_is_clear = false;
}

/**Add a wrong move to the counter*/
void GameState::add_wrong_move() {
    current_board_wrong_moves++;
    std::cout << "Wrong move; " << current_board_wrong_moves << " total" << std::endl;
}

/**@return number of blocks removed from the board*/
int GameState::get_blocks_removed() {return current_board_block_removed;}

/**Add a removed block to the counter*/
void GameState::increment_blocks_removed() {current_board_block_removed++;}

/**Sets that the board is clear*/
void GameState::set_is_clear() {current_board_is_clear = true;}

/**@return if the board is clear*/
bool GameState::get_is_clear() {return current_board_is_clear;}

/**@return highest level the player has completed*/
int GameState::get_max_level() {return max_level;}

/**Gets the current level*/
int GameState::get_cur_level() {return cur_level;}

/**Sets the current level, updates max level if necessary*/
void GameState::set_cur_level(int lvl) {
    cur_level = lvl;
    if (lvl > max_level) {max_level = lvl;}
}

/**Adds 1 to cur_level, possibly increases max_level*/
void GameState::increment_cur_level() {
    cur_level++;
    if (cur_level > max_level) {max_level = cur_level;}
}
