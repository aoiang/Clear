#include "GameState.hpp"

GameState::GameState(std::string) {}

void GameState::init_current_board() {
    current_board_wrong_moves = 0;
    current_board_block_removed = 0;
    current_board_is_clear = false;
}

void GameState::add_wrong_move() {
    current_board_wrong_moves++;
    std::cout << "Wrong move; " << current_board_wrong_moves << " total" << std::endl;
}

int GameState::get_blocks_removed() {return current_board_block_removed;}

void GameState::increment_blocks_removed() {current_board_block_removed++;}

void GameState::set_is_clear() {current_board_is_clear = true;}

bool GameState::get_is_clear() {return current_board_is_clear;}
