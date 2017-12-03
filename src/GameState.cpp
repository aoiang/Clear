#include "GameState.hpp"

GameState::GameState(std::string) {}

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
