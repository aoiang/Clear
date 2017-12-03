#include "GameState.hpp"

GameState::GameState(std::string) {}

void GameState::init_current_board() {
    current_board_wrong_moves = 0;
}

void GameState::add_wrong_move() {
    current_board_wrong_moves++;
    std::cout << "Wrong move; " << current_board_wrong_moves << " total" << std::endl;
}
