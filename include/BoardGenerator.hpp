#ifndef CLEAR_BOARD_GENERATOR_HPP
#define CLEAR_BOARD_GENERATOR_HPP

#include "GameLogic.hpp"
#include "BoardState.hpp"
#include <random>

class BoardGenerator {
    private:
        GameLogic generator_logic;
        GameState * state;
        BoardState * board;
        static const int number_of_configs = 94;
        void add_block_if_possible(int x, int y);
        std::mt19937 get_random_num_generator();
        std::mt19937 number_generator;
        std::string pick_config();
        int pick_number_between(int min, int max);
    public:
        BoardGenerator();
        BoardState * make_board(int width, int height);
        BoardState * make_board(int width, int height, std::string filepath);
};

#endif //CLEAR_BOARD_GENERATOR_HPP
